/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/13 19:55:27 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*create_comand(t_shell *tshell, t_list *token, size_t pos)
{
	t_cmd	*comand;

	comand = ft_calloc(sizeof(t_cmd), 1);
	if (!comand)
		return (NULL);
	return (comand);
}

void	split_intocomands(t_shell *tshell)
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_list	*tokens;

	if (!tshell->tokens)
		return ;
	tokens = tshell->tokens;
	while (tokens)
	{
		tmp = ft_lstnew(create_comand(tshell, tokens, i));
		tokens = tokens->next;
	}
}
