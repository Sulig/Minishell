/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:50:51 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/26 20:15:33 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_toktype(t_token *token, t_list *next)
{
	if (token->toktype == REDIR || token->toktype == PIPE)
		return (-1);
	else if (token->toktype == ARGS)
		return (1);
	else if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
	{
		if (next)
			return (1);
		else if (!next)
			return (-1);
	}
	else if (token->toktype != SPACE)
		return (1);
	return (0);
}

static int	checkfor_prestuff(t_list *list, enum e_toktype mode)
{
	t_token	*token;
	t_list	*tmp;
	size_t	finded;

	finded = 0;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode)
		{
			finded++;
			if (!list->prev)
				return (0);
			tmp = list->prev;
			while (tmp)
			{
				token = (t_token *)tmp->content;
				if (check_toktype(token, NULL) != 0)
					return (check_toktype(token, NULL));
				tmp = tmp->prev;
			}
		}
		list = list->next;
	}
	if (!finded)
		return (1);
	return (0);
}

static int	checkfor_aftstuff(t_list *list, enum e_toktype mode)
{
	t_token	*token;
	size_t	finded;

	finded = 0;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode)
		{
			finded++;
			if (!list->next)
				return (0);
			while (list->next)
			{
				list = list->next;
				token = (t_token *)list->content;
				if (check_toktype(token, list->next) != 0)
					return (check_toktype(token, list->next));
			}
		}
		list = list->next;
	}
	if (!finded)
		return (1);
	return (0);
}

static int	is_valid(t_list *list, enum e_toktype mode)
{
	if (mode == PIPE)
		if (checkfor_prestuff(list, mode) > 0)
			if (checkfor_aftstuff(list, mode) > 0)
				return (1);
	if (mode != PIPE)
		if (checkfor_aftstuff(list, mode) > 0)
			return (1);
	return (0);
}

int	check_valid_syntax(t_shell *tshell)
{
	if (!tshell->tokens && !tshell->line)
	{
		tshell->exit_state = 1;
		return (0);
	}
	if (!is_valid(tshell->tokens, REDIR))
	{
		tshell->exit_state = 1;
		return (print_err_syntax(NULL));
	}
	if (!is_valid(tshell->tokens, PIPE))
	{
		tshell->exit_state = 1;
		return (print_err_syntax("|"));
	}
	return (1);
}
