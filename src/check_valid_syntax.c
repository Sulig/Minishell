/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:50:51 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/21 20:04:16 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_toktype(t_token *token, enum e_toktype mode, int ok)
{
	if (!token)
		return (0);
	if (token->toktype == PIPE)
		if (token->location == NO_QUOTED)
			return (-1);
	if (token->toktype == REDIR)
	{
		//if (mode == PIPE && ok)
			//return (0);
		ok = 0;
		mode = TNULL;
		if (token->location == NO_QUOTED)
			return (-1);
	}
	if (token->toktype != SPACE)
		return (1);
	return (0);
}

static t_token	*return_type(t_token *act, t_token *ret)
{
	int	check;

	check = check_toktype(act, act->toktype, 0);
	if (check == 1)
		return (NULL);
	if (check == -1)
		return (ret);
	return (ret);
}

static t_token	*checkfor_befstuff(t_list *list, enum e_toktype mode)
{
	t_token	*token;
	t_token	*act;
	t_list	*tmp;

	act = NULL;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode && token->location == NO_QUOTED)
		{
			act = token;
			if (!list->prev)
				return (act);
			tmp = list->prev;
			while (tmp)
			{
				token = (t_token *)tmp->content;
				if (check_toktype(token, mode, 0) != 0)
					return (return_type(token, act));
				tmp = tmp->prev;
			}
		}
		list = list->next;
	}
	return (act);
}

static t_token	*checkfor_atfstuff(t_list *list, enum e_toktype mode)
{
	t_token	*token;
	t_token	*act;

	act = NULL;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode && token->location == NO_QUOTED)
		{
			act = token;
			if (!list->next)
				return (act);
			while (list->next)
			{
				list = list->next;
				token = (t_token *)list->content;
				if (check_toktype(token, mode, 1) != 0)
					return (return_type(token, act));
			}
		}
		list = list->next;
	}
	return (act);
}

int	check_valid_syntax(t_shell *tshell)
{
	t_list	*list;
	t_token	*ch_bef;
	t_token	*ch_aft;

	if (!tshell)
		return (0);
	if (!tshell->tokens)
		return (1);
	list = tshell->tokens;
	ch_bef = checkfor_befstuff(list, PIPE);
	ch_aft = checkfor_atfstuff(list, PIPE);
	if (ch_aft || ch_bef)
	{
		tshell->exit_state = 258;
		if (ch_bef)
			return (print_err_syntax(ch_bef->content));
		return (print_err_syntax(ch_aft->content));
	}
	ch_aft = checkfor_atfstuff(list, REDIR);
	if (ch_aft)
	{
		tshell->exit_state = 258;
		return (print_err_syntax(ch_aft->content));
	}
	return (1);
}
