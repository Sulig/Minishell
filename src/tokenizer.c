/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:19:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/20 18:46:51 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static enum	e_toktype	scan_toktype(char c)
{
	if (!c)
		return (TNULL);
	else if (c == ' ')
		return (SPACE);
	else if (c == '$')
		return (ENV);
	else if (c == '-')
		return (FLAG);
	else if (c == 34)
		return (D_QUOTE);
	else if (c == 39)
		return (S_QUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '>')
		return (REDIR_OUT);
	return (ARGS);
}

static size_t	len_of_content(char *line)
{
	size_t	len;

	len = 0;
	if (!line)
		return (0);
	while (line[len])
	{
		if (!ft_isalnum(line[len]) && line[len] != '_')
			if (line[len] != '?')
				return (len);
		len++;
	}
	return (len);
}

static char	*fill_content(t_shell *tshell, size_t pos)
{
	size_t	i;
	size_t	len;
	char	*content;

	i = pos;
	content = NULL;
	while (scan_toktype(tshell->line[i]) == ARGS)
		i++;
	len = i - pos;
	if (!len)
	{
		len++;
		if (scan_toktype(tshell->line[i]) == REDIR_IN)
			if (scan_toktype(tshell->line[i + 1]) == REDIR_IN)
				len = 2;
		if (scan_toktype(tshell->line[i]) == REDIR_OUT)
			if (scan_toktype(tshell->line[i + 1]) == REDIR_OUT)
				len = 2;
		if (scan_toktype(tshell->line[i]) == ENV)
			len += len_of_content(tshell->line + pos + 1);
	}
	content = ft_substr(tshell->line, pos, len);
	return (content);
}

static t_token	*create_token(t_shell *tshell, size_t pos)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->toktype = scan_toktype(tshell->line[pos]);
	if (token->toktype == FLAG && pos > 0)
		if (scan_toktype(tshell->line[pos - 1]) != SPACE)
			token->toktype = ARGS;
	if (token->toktype == FLAG)
		if (scan_toktype(tshell->line[pos + 1]) == SPACE)
			token->toktype = ARGS;
	if (token->toktype == REDIR_IN)
		if (scan_toktype(tshell->line[pos + 1]) == REDIR_IN)
			token->toktype = REDIR_DEL;
	if (token->toktype == REDIR_OUT)
		if (scan_toktype(tshell->line[pos + 1]) == REDIR_OUT)
			token->toktype = REDIR_APP;
	token->content = fill_content(tshell, pos);
	token->location = NO_QUOTED;
	if (token->toktype == REDIR_IN || token->toktype == REDIR_OUT)
		token->toktype = REDIR;
	if (token->toktype == REDIR_APP || token->toktype == REDIR_DEL)
		token->toktype = REDIR;
	return (token);
}

void	split_intotokens(t_shell *tshell)
{
	t_list	*tmp;
	t_token	*token;
	size_t	i;

	i = 0;
	tmp = NULL;
	if (!tshell->line)
		return ;
	while (tshell->line[i])
	{
		tmp = ft_lstnew(create_token(tshell, i));
		token = (t_token *)tmp->content;
		ft_lstadd_back(&tshell->tokens, tmp);
		i += ft_strllen(token->content);
		if (!ft_strllen(token->content))
			i++;
		if (token->toktype == REDIR_DEL || token->toktype == REDIR_APP)
			i++;
	}
	tshell->tok_size = ft_lstsize(tshell->tokens);
	tshell->tokens = fill_token_location(tshell->tokens);
}
