#include "../../include/minishell.h"

t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	if (!tokens)
		return (cmd);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(0, token);
		if (token->toktype == SPACE)
			cmd->flags = push_intoarr(cmd->flags, token);
		else if (checker == -1 || checker == 1)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker == 3)
		{
			cmd->flags = push_intoarr(cmd->flags, token);
			tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
		}
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}

