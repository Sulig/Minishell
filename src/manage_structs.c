/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:47:15 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/08 19:13:37 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_shell *tshell)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tshell->tokens;
	while (tshell->tsize--)
	{
		token = (t_token *)tmp->content;
		if (token->content)
			token->content = ft_free_str(token->content);
		tmp = tmp->next;
	}
	ft_lstclear(&tshell->tokens, free);
}

void	*free_tshell(t_shell *tshell)
{
	if (!tshell)
		return (NULL);
	tshell->env = ft_auto_free_arr(tshell->env);
	if (tshell->tokens && tshell->tsize)
		free_tokens(tshell);
	free(tshell);
	return (NULL);
}

t_shell	*init_tshell(t_shell *tshell, char **env)
{
	tshell = ft_calloc(sizeof(t_shell), 1);
	if (!tshell)
		return (NULL);
	tshell->env = ft_strarrdup(env);
	if (!tshell->env)
		return (free_tshell(tshell));
	tshell->line = NULL;
	tshell->tokens = NULL;
	tshell->tsize = 0;
	return (tshell);
}
