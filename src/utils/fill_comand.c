/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:10:07 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/27 18:11:06 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker == 1)
			break ;
		cmd->flags = push_intoarr(cmd->flags, token);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}

t_cmd	*fill_comand_args(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	ft_printf("Position: %u\n", *pos);
	tokens = ft_lstgetnode(tokens, *pos);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		cmd->input = push_intoarr(cmd->input, token);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}
