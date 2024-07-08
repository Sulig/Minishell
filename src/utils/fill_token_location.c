/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:10:13 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/24 18:41:59 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_quote_type(enum e_toktype toktype, int quoted)
{
	if (toktype == S_QUOTE)
	{
		if (!quoted)
			return (1);
		else if (quoted == 1)
			return (0);
	}
	if (toktype == D_QUOTE)
	{
		if (!quoted)
			return (2);
		if (quoted == 2)
			return (0);
	}
	return (quoted);
}

t_list	*fill_token_location(t_list *tokens)
{
	t_list	*first;
	t_token	*token;
	int		quoted;

	first = tokens;
	quoted = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		quoted = set_quote_type(token->toktype, quoted);
		if (quoted == 1 && token->toktype != S_QUOTE)
		{
			token->location = IN_SINGLE_Q;
			token->toktype = ARGS;
		}
		if (quoted == 2 && token->toktype != D_QUOTE)
		{
			token->location = IN_DOUBLE_Q;
			if (token->toktype != ENV)
				token->toktype = ARGS;
		}
		tokens = tokens->next;
	}
	return (first);
}
