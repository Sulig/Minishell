/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agroup_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:23:06 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/09 19:55:24 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*fill_quote_case(t_token *new_t, t_list *tokens, size_t *pos)
{
	t_token	*act;
	int		checker;

	while (tokens)
	{
		act = (t_token *)tokens->content;
		new_t->content = ft_strjoin_free_fst(new_t->content, act->content);
		checker = check_beforecreate(NULL, act);
		if (checker == 2)
		{
			*pos = *pos + 1;
			break ;
		}
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (new_t);
}

static t_token	*fill_flags_case(t_token *new_t, t_list *tokens, size_t *pos)
{
	t_token	*act;
	int		checker;

	while (tokens)
	{
		act = (t_token *)tokens->content;
		new_t->content = ft_strjoin_free_fst(new_t->content, act->content);
		checker = check_beforecreate(NULL, act);
		if (checker == 0)
		{
			*pos = *pos + 1;
			break ;
		}
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (new_t);
}

static t_token	*create_token(t_list *tokens, t_token *token, size_t *pos)
{
	t_token	*new_t;
	char	*tmp;
	int		checker;

	new_t = duplicate_token(token);
	if (!new_t)
		return (NULL);
	checker = check_beforecreate(NULL, token);
	//Revise case-> echo-l
	if (checker == -1 || checker == 1 || checker == 0)
		return (new_t);
	else if (checker == 2)
		new_t = fill_quote_case(new_t, tokens->next, pos);
	else if (checker == 3)
		new_t = fill_flags_case(new_t, tokens->next, pos);
	tmp = ft_strtrim_s(new_t->content, " ");
	new_t->content = ft_strremplace(new_t->content, tmp);
	tmp = ft_free_str(tmp);
	return (new_t);
}

t_list	*agroup_tokens(t_list *tokens)
{
	t_list	*new_list;
	t_list	*tmp;
	t_token	*token;
	size_t	pos;

	new_list = NULL;
	tmp = NULL;
	while (tokens)
	{
		pos = 0;
		token = (t_token *)tokens->content;
		tmp = ft_lstnew(create_token(tokens, token, &pos));
		ft_lstadd_back(&new_list, tmp);
		tokens = ft_lstgetnode(tokens, pos);
		if (tokens)
			tokens = tokens->next;
	}
	return (new_list);
}

void	agroup_mylist(t_shell *tshell)
{
	t_list	*new_list;

	new_list = agroup_tokens(tshell->tokens);
	free_tokens(tshell);
	tshell->tokens = new_list;
	tshell->tok_size = ft_lstsize(tshell->tokens);
}
