/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:10:13 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/15 17:32:49 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_quote_type(enum e_toktype toktype, int quoted)
{
	if (toktype == S_QUOTE)
	{
		if (!quoted)
			return (1);
		else if (quoted == 1)
			return (0);
	}
	if (toktype == D_QUOTE)
	{
		if (!quoted)
			return (2);
		if (quoted == 2)
			return (0);
	}
	return (quoted);
}

t_list	*fill_token_location(t_list *tokens)
{
	t_list	*first;
	t_token	*token;
	int		quoted;

	first = tokens;
	quoted = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		quoted = set_quote_type(token->toktype, quoted);
		if (quoted == 1 && token->toktype != S_QUOTE)
		{
			token->location = IN_SINGLE_Q;
			token->toktype = ARGS;
		}
		if (quoted == 2 && token->toktype != D_QUOTE)
		{
			token->location = IN_DOUBLE_Q;
			if (token->toktype != ENV)
				token->toktype = ARGS;
		}
		tokens = tokens->next;
	}
	return (first);
}

/*
* Joins tokens of type ARGS if they are siblings
* 	* Supose case -> `cmd-a`
*	* `cmd` <-> `-` <-> `a`
*	* So with this function will be: `cmd-a`
*/
t_token	*fill_args_case(t_token *new_t, t_list *tokens, size_t *pos)
{
	t_token	*act;
	int		checker;

	while (tokens)
	{
		act = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, act);
		if (checker != 1)
			break ;
		new_t->content = ft_strjoin_free_fst(new_t->content, act->content);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (new_t);
}

void	select_nextpos(t_cmd *cmd, t_token *token, size_t *pos)
{
	if (cmd->cmdtype == PIPE || cmd->cmdtype == REDIR)
	{
		if (check_beforecreate(NULL, token))
			*pos = *pos -1 ;
		return ;
	}
	if (check_beforecreate(NULL, token) == -1)
		*pos = *pos - 1;
}
