/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillcomands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/28 19:19:11 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*jump_tocontent(t_list *tokens, size_t *pos)
{
	t_token *token;

	token = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (check_beforecreate(NULL, token) != 0)
			break ;
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (token);
}
