/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/14 19:52:04 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	checkfor_prestuff(t_list *list, enum e_toktype mode, int tok)
{
	t_token	*token;
	t_list	*tmp;

	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode)
		{
			tok = 1;
			tmp = list;
			if (!tmp->prev)
				return (0);
			while (tmp->prev)
			{
				tmp = tmp->prev;
				token = (t_token *)tmp->content;
				if (token->toktype == ARGS)
					return (1);
			}
		}
		list = list->next;
	}
	if (!tok)
		return (1);
	return (0);
}

static int	checkfor_aftstuff(t_list *list, enum e_toktype mode)
{
	t_token	*token;
	int		tok;

	tok = 0;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype == mode)
		{
			tok = 1;
			if (!list->next)
				return (0);
			while (list->next)
			{
				list = list->next;
				token = (t_token *)list->content;
				if (token->toktype == ARGS)
					return (1);
			}
		}
		list = list->next;
	}
	if (!tok)
		return (1);
	return (0);
}

static int	is_valid(t_list *list, enum e_toktype mode)
{
	if (mode == PIPE)
		if (checkfor_prestuff(list, mode, 0))
			if (checkfor_aftstuff(list, mode))
				return (1);
	if (mode == REDIR_DEL)
		if (checkfor_prestuff(list, mode, 0))
			if (checkfor_aftstuff(list, mode))
				return (1);
	if (mode != PIPE && mode != REDIR_DEL)
		if (checkfor_aftstuff(list, mode))
			return (1);
	return (0);
}

void	split_intocomands(t_shell *tshell)
{
	int	printed;

	printed = 0;
	if (!tshell->tokens)
		return ;
	if (!is_valid(tshell->tokens, REDIR))
	{
		print_err_syntax(NULL);
		return ;
	}
	if (!is_valid(tshell->tokens, PIPE))
	{
		print_err_syntax("|");
		return ;
	}
}
