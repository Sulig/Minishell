/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:45:41 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/06 19:50:43 by sadoming         ###   ########.fr       */
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
	else
		return (ARGS);
}

t_token	*create_token(char elem, char *command, size_t pos)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->toktype = scan_toktype(elem);
	if (token->toktype == OPTION)
		if (scan_toktype(command[pos + 1]) == TNULL)
			token->toktype = ARGS;
	if (token->toktype == REDIR_IN)
		if (scan_toktype(command[pos + 1]) == REDIR_IN)
			token->toktype = REDIR_DEL;
	if (token->toktype == REDIR_OUT)
		if (scan_toktype(command[pos + 1]) == REDIR_OUT)
			token->toktype = REDIR_APP;
	token->comand = NULL;
	token->options = NULL;
	token->args = NULL;
	return (token);
}

t_shell	*split_intotokens(char *command, t_shell *tshell)
{
	t_token	*token;
	t_list	*tmp;
	size_t	i;
	size_t	toktype;

	i = 0;
	tmp = NULL;
	if (!ft_strllen(command))
		return (NULL);
	while (!tshell->tokens && command[i])
	{
		if (scan_toktype(command[i]) != TNULL)
			tshell->tokens = ft_lstnew(create_token(command[i], command, i));
		i++;
	}
	while (command[i])
	{
		toktype = scan_toktype(command[i]);
		if (toktype != TNULL)
		{
			tmp = ft_lstnew(create_token(command[i], command, i));
			ft_lstadd_back(&tshell->tokens, tmp);
		}
		i++;
	}
	tshell->tsize = ft_lstsize(tshell->tokens);
	ft_printf("Number of tokens created: %u\n", tshell->tsize);
	token = (t_token *)tshell->tokens->content;
	ft_printf("Type of 1st token = %d\n", token->toktype);
	return (tshell);
}
