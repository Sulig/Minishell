/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfor_unclosedquotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:59:11 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/21 19:51:58 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*unclosed_dquote(t_list *tokens)
{
	t_list	*first;
	t_list	*pos;
	t_token	*token;
	size_t	dquotes;

	first = tokens;
	dquotes = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == D_QUOTE && token->location != IN_SINGLE_Q)
		{
			dquotes++;
			pos = tokens;
		}
		tokens = tokens->next;
	}
	if (dquotes % 2)
	{
		token = (t_token *)pos->content;
		if (pos->next)
			token = (t_token *)pos->next->content;
		return (token->content);
	}
	return (NULL);
}

static char	*unclosed_squote(t_list *tokens)
{
	t_list	*first;
	t_list	*pos;
	t_token	*token;
	size_t	dquotes;

	first = tokens;
	dquotes = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == S_QUOTE && token->location != IN_DOUBLE_Q)
		{
			dquotes++;
			pos = tokens;
		}
		tokens = tokens->next;
	}
	if (dquotes % 2)
	{
		token = (t_token *)pos->content;
		if (pos->next)
			token = (t_token *)pos->next->content;
		return (token->content);
	}
	return (NULL);
}

int	checkfor_unclosedquotes(t_shell *tshell, t_list *tokens)
{
	char	*check_dquotes;
	char	*check_squotes;
	size_t	pos_of_error;

	check_dquotes = unclosed_dquote(tokens);
	check_squotes = unclosed_squote(tokens);
	if (!check_dquotes && !check_squotes)
		return (1);
	if (ft_strllen(check_dquotes) > ft_strllen(check_squotes))
		pos_of_error = ft_cnt_tostr(tshell->line, check_dquotes);
	if (ft_strllen(check_squotes) > ft_strllen(check_dquotes))
		pos_of_error = ft_cnt_tostr(tshell->line, check_squotes);
	if (pos_of_error)
		pos_of_error--;
	tshell->exit_state = 1;
	return (print_err_syntax(tshell->line + pos_of_error));
}
