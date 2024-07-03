/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillcomands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/03 19:30:31 by sadoming         ###   ########.fr       */
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

t_token	**clean_array(t_token **tokens)
{
	size_t	j;

	j = -1;
	if (tokens[0]->toktype == SPACE)
	{
		tokens = clear_tarr(tokens);
		return (tokens);
	}
	while (tokens[++j])
	{
		if (tokens[j]->toktype == SPACE && tokens[j + 1])
		{
			if (tokens[j + 1]->toktype == SPACE)
			{
				tokens = pop_outarr(tokens, j);
				j = -1;
			}
		}
		if (!tokens)
			return (tokens);
	}
	if (tokens)
		if (tokens[len_of_tokens(tokens) - 1]->toktype == SPACE)
			tokens = pop_outarr(tokens, len_of_tokens(tokens) - 1);
	return (tokens);
}
