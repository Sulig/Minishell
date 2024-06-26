/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:10:07 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/26 19:38:21 by sadoming         ###   ########.fr       */
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
		if (checker == -1 || checker == 1)
		{
			*pos = *pos - 1;
			break ;
		}
		cmd->flags = push_intoarr(cmd->flags, token);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}

