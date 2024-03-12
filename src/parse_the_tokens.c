/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/12 19:37:06 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->toktype != ARGS)
		return (0);
	return (1);
}

long	comand_counter(t_list *tokens)
{
	long	cnt;
	t_token	*token;

	cnt = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == PIPE)
		{
			if (!is_valid(tokens->next))
				return (-1);
			cnt++;
		}
		if (token->toktype == REDIR_OUT)
			if (!is_valid(tokens->next))
				return (-1);
		tokens = tokens->next;
	}
	return (cnt);
}
