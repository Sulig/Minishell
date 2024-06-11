/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:35:23 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/28 18:57:20 by sadoming         ###   ########.fr       */
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
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '\'')
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

static t_token	*create_token(char *line, size_t pos)
{
	t_token	*token;
	size_t	i;
	size_t	len;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->toktype = scan_toktype(line[pos]);
	i = pos;
	while (scan_toktype(line[i]) == ARGS)
		i++;
	len = i - pos;
	if (!len)
	{
		len++;
		if (scan_toktype(line[i]) == ENV)
			len += len_of_content(line + pos + 1);
		if (scan_toktype(line[i]) == ENV && len == 1)
			token->toktype = ARGS;
	}
	token->content = ft_substr(line, pos, len);
	if (!ft_strllen(token->content))
		token->content = ft_free_str(token->content);
	return (token);
}

t_list	*split_intotokens_forexpand(char *line)
{
	t_list	*tmp;
	t_list	*tokens;
	t_token	*token;
	size_t	i;

	i = 0;
	tmp = NULL;
	tokens = NULL;
	if (!ft_strllen(line))
		return (NULL);
	while (line[i])
	{
		tmp = ft_lstnew(create_token(line, i));
		token = (t_token *)tmp->content;
		ft_lstadd_back(&tokens, tmp);
		i += ft_strllen(token->content);
		if (!ft_strllen(token->content))
			i++;
	}
	return (tokens);
}

t_list	*free_tokens_list(t_list **tokens)
{
	t_list	*tmp;
	t_token	*token;
	size_t	size;

	tmp = *tokens;
	if (*tokens)
	{
		size = ft_lstsize(*tokens);
		while (size--)
		{
			token = (t_token *)tmp->content;
			token->content = ft_free_str(token->content);
			tmp = tmp->next;
		}
	}
	ft_lstclear(tokens, free);
	return (NULL);
}
