#include "../../include/minishell.h"

static t_cmd	*join_option(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens->next)
		return (cmd);
	tokens = tokens->next;
	token = (t_token *)tokens->content;
	if (token->toktype == FLAG)
		return (cmd);
	cmd->flags = ft_strjoin_free_fst(cmd->flags, "-");
	cmd->flags = ft_strjoin_free_fst(cmd->flags, token->content);
	if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
	{
		while (tokens->next)
		{
			*pos = *pos + 1;
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
				break ;
			cmd->flags = ft_strjoin_free_fst(cmd->flags, token->content);
		}
		cmd->flags = ft_strjoin_free_fst(cmd->flags, token->content);
	}
	*pos = *pos + 1;
	return (cmd);
}

