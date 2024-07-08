/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfor_unclosedquotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:59:11 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/26 19:29:12 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*unclosed_dquote(t_list *tokens)
{
	t_token	*token;
	size_t	quotes;

	quotes = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == D_QUOTE)
		{
			quotes = ft_apears_ch_in_str(token->content, '\"');
			if (quotes % 2)
				return (token->content);
		}
		tokens = tokens->next;
	}
	return (NULL);
}

static char	*unclosed_squote(t_list *tokens)
{
	t_token	*token;
	size_t	quotes;

	quotes = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == S_QUOTE)
		{
			quotes = ft_apears_ch_in_str(token->content, '\'');
			if (quotes % 2)
				return (token->content);
		}
		tokens = tokens->next;
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
	tshell->exit_state = 258;
	return (print_err_syntax(tshell->line + pos_of_error));
}
