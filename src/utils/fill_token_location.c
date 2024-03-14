/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:10:13 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/14 18:22:00 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_list	*detect_doublequotes(t_list *tokens)
{
	t_list	*first;
	t_token	*token;
	int		quoted;

	first = tokens;
	while (tokens)
	{
		quoted = 0;
		token = (t_token *)tokens->content;
		if (token->toktype == D_QUOTE)
			quoted = 2;
		while (quoted == 2 && tokens->next)
		{
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			if (token->toktype != D_QUOTE)
				token->location = IN_DOUBLE_Q;
			else
				quoted = 0;
			tokens->content = token;
		}
		tokens = tokens->next;
	}
	tokens = first;
	return (first);
}

static t_list	*detect_singlequotes(t_list *tokens)
{
	t_list	*first;
	t_token	*token;
	int		quoted;

	first = tokens;
	while (tokens)
	{
		quoted = 0;
		token = (t_token *)tokens->content;
		if (token->toktype == S_QUOTE)
			quoted = 2;
		while (quoted == 2 && tokens->next)
		{
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			if (token->toktype != S_QUOTE)
				token->location = IN_SINGLE_Q;
			else
				quoted = 0;
			tokens->content = token;
		}
		tokens = tokens->next;
	}
	tokens = first;
	return (first);
}

void	fill_token_location(t_shell *tshell)
{
	tshell->tokens = detect_doublequotes(tshell->tokens);
	tshell->tokens = detect_singlequotes(tshell->tokens);
}
