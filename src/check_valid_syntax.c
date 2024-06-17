/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:50:51 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/17 20:06:43 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_toktype(t_token *token, enum e_toktype mode, int ok)
{
	if (!token)
		return (-1);
	if (token->toktype == REDIR && token->location == NO_QUOTED)
		if (ok)
			return (-1);
	if (token->toktype == mode && token->location == NO_QUOTED)
		return (-1);
	if (token->toktype != SPACE)
		return (1);
	return (0);
}

static int	checkif_isvalid(enum e_toktype mode, t_list *node)
{
	t_list	*tmp;
	t_token	*act;

	tmp = node;
	while (node->next)
	{
		node = node->next;
		act = (t_token *)node->content;
		if (check_toktype(act, mode, 0) == -1)
			return (0);
		else if (check_toktype(act, mode, 0) == 1 && mode == PIPE)
			break ;
		else if (check_toktype(act, mode, 0) == 1)
			return (1);
	}
	while (tmp->prev && mode == PIPE)
	{
		tmp = tmp->prev;
		act = (t_token *)tmp->content;
		if (check_toktype(act, mode, 1) == -1)
			return (0);
		else if (check_toktype(act, mode, 1) == 1)
			return (1);
	}
	return (0);
}

t_token	*checkfor_mode(enum e_toktype mode, t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode)
		{
			if (!list->next)
				return (token);
			if (!list->prev && mode == PIPE)
				return (token);
			if (!checkif_isvalid(mode, list))
				return (token);
		}
		list = list->next;
	}
	return (NULL);
}

int	check_valid_syntax(t_shell *tshell)
{
	t_list	*list;
	t_token	*checker;

	list = tshell->tokens;
	checker = checkfor_mode(PIPE, list);
	if (checker)
	{
		tshell->exit_state = print_err_syntax(checker->content);
		return (tshell->exit_state);
	}
	checker = checkfor_mode(REDIR, list);
	if (checker)
	{
		tshell->exit_state = print_err_syntax(checker->content);
		return (tshell->exit_state);
	}
	return (0);
}
