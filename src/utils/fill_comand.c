/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:10:07 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/25 19:47:21 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	**t_join_case(t_token **args, char *tojoin, size_t pos, char pcase)
{
	char	*tmp;

	if (!args)
		return (NULL);
	else if (!args[pos])
		return (NULL);
	tmp = args[pos]->content;
	if (pcase == '>')
		tmp = ft_strjoin_free_fst(tmp, tojoin);
	if (pcase == '<')
		tmp = ft_strjoin_free_sec(tojoin, tmp);
	args[pos]->content = tmp;
	return (args);
}

t_cmd	*join_options(t_cmd *cmd, t_list *tokens, t_token *tok, size_t *pos)
{
	int		checker;
	size_t	a;

	cmd->flags = push_intoarr(cmd->flags, tok);
	a = len_of_tokens(cmd->flags) - 1;
	while (tokens->next)
	{
		tokens = tokens->next;
		*pos = *pos + 1;
		tok = (t_token *)tokens->content;
		checker = check_beforecreate(0, tok);
		if (checker == -1 || checker == 0 || checker == 3)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker != 3)
			cmd->flags = t_join_case(cmd->flags, tok->content, a, '>');
	}
	return (cmd);
}

t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(0, token);
		if (checker == -1 || checker == 1)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (token->toktype == FLAG)
		{
			cmd = join_options(cmd, tokens, token, pos);
			tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
		}
		if (!tokens)
			break ;
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}
