/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:03:35 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/29 19:56:24 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*join_option(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens->next)
		return (cmd);
	cmd->options = ft_strjoin_free_fst(cmd->options, "-");
	tokens = tokens->next;
	token = tokens->content;
	cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
	*pos = *pos + 1;
	return (cmd);
}

t_cmd	*fill_comand_options(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens)
		return (cmd);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == SPACE)
			cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
		if (check_beforecreate(NULL, token) == -1 || token->toktype == ARGS)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (check_beforecreate(NULL, token) == 3)
		{
			cmd = join_option(cmd, tokens, pos);
			tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
		}
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	if (!tokens)
		*pos = *pos - 1;
	return (cmd);
}
