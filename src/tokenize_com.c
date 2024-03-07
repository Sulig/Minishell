/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:45:41 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:05 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

enum	e_toktype	scan_toktype(char c)
{
	if (c == ' ')
		return (TNULL);
	else if (c == '$')
		return (ENV);
	else if (c == '-')
		return (OPTION);
	else if (c == '"')
		return (D_QUOTE);
	else if (c == 39)
		return (S_QUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '>')
		return (REDIR_OUT);
	else
		return (ARGS);
}

char	*fill_content(size_t *pos, t_shell *tshell)
{
	size_t		i;
	char		*content;
	static int	d_quote;

	i = *pos;
	content = NULL;
	while (tshell->line[i])
	{
		if (d_quote)
		{
			if (scan_toktype(tshell->line[i]) == TNULL)
				i++;
			else if (scan_toktype(tshell->line[i]) != ARGS)
				break ;
		}
		else if (scan_toktype(tshell->line[i]) != ARGS)
			break ;
		i++;
	}
	content = ft_substr(tshell->line, *pos, i - *pos);
	*pos = i;
	return (content);
}

t_token	*create_token(t_shell *tshell, size_t *pos)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->toktype = scan_toktype(tshell->line[*pos]);
	if (token->toktype == OPTION)
		if (scan_toktype(tshell->line[*pos + 1]) == TNULL)
			token->toktype = ARGS;
	if (token->toktype == REDIR_IN)
		if (scan_toktype(tshell->line[*pos + 1]) == REDIR_IN)
			token->toktype = REDIR_DEL;
	if (token->toktype == REDIR_OUT)
		if (scan_toktype(tshell->line[*pos + 1]) == REDIR_OUT)
			token->toktype = REDIR_APP;
	if (!tshell->d_quote && token->toktype == D_QUOTE)
		tshell->d_quote = 1;
	else if (tshell->d_quote && token->toktype == D_QUOTE)
		tshell->d_quote = 0;
	token->content = fill_content(pos, tshell);
	return (token);
}

t_shell	*split_intotokens(t_shell *tshell)
{
	t_list	*tmp;
	size_t	i;
	size_t	toktype;

	i = 0;
	tmp = NULL;
	if (!ft_strllen(tshell->line))
		return (NULL);
	while (tshell->line[i])
	{
		toktype = scan_toktype(tshell->line[i]);
		if (toktype != TNULL)
		{
			tmp = ft_lstnew(create_token(tshell, &i));
			ft_lstadd_back(&tshell->tokens, tmp);
		}
		i++;
	}
	tshell->tsize = ft_lstsize(tshell->tokens);
	print_tokens_st(tshell->tokens);
	return (tshell);
}
