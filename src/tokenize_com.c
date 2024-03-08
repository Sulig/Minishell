/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:45:41 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/08 19:10:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

enum	e_toktype	scan_toktype(char c)
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

char	*fill_content(t_shell *tshell, size_t pos)
{
	size_t	i;
	char	*content;

	i = pos;
	content = NULL;
	while (scan_toktype(tshell->line[i]) == ARGS)
		i++;
	content = ft_substr(tshell->line, pos, i - pos);
	if (!ft_strllen(content))
		content = ft_free_str(content);
	return (content);
}

t_token	*create_token(t_shell *tshell, size_t pos)
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
	token->cont_len = ft_strllen(token->content);
	return (token);
}

t_shell	*split_intotokens(t_shell *tshell)
{
	t_list	*tmp;
	t_token	*token;
	size_t	i;

	i = 0;
	tmp = NULL;
	if (!ft_strllen(tshell->line))
		return (NULL);
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
	tshell->tsize = ft_lstsize(tshell->tokens);
	print_tokens_st(tshell->tokens);
	return (tshell);
}
