/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:19:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/13 19:55:10 by sadoming         ###   ########.fr       */
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
		return (OPTION);
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
			len++;
		else
			if (scan_toktype(tshell->line[i]) == REDIR_OUT)
				len++;
	}
	content = ft_substr(tshell->line, pos, len);
	if (!ft_strllen(content))
		content = ft_free_str(content);
	return (content);
}

static t_token	*create_token(t_shell *tshell, size_t pos)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->toktype = scan_toktype(tshell->line[pos]);
	if (token->toktype == OPTION)
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
	return (token);
}

static t_list *fill_token_location(t_list *tokens)
{
	t_list	*first;
	t_token	*token;

	first = tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		while (token->toktype != D_QUOTE)
		{
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			if (token->toktype != D_QUOTE)
				token->location = IN_DOUBLE_Q;
			tokens->content = token;
		}
		tokens = tokens->next;
	}
	tokens = first;
	return (tokens);
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
