/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_echo      .c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:20:47 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/04 16:58:26 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* put the word after redir in the echo imput to print it to redirection*/
void	prepare_echo(t_list *piped_cmd)
{
	t_list	*node;
	t_cmd	*next_cmd;
	t_cmd	*cmd;
	t_token	*tok;

	cmd = piped_cmd->content;
	node = piped_cmd->next;
	while (node)
	{
		next_cmd = node->content;
		if (next_cmd->cmdtype != REDIR)
		{
			tok = ft_calloc(sizeof(t_token), 1);
			tok->content = ft_strdup(next_cmd->name->content);
			tok->location = NO_QUOTED;
			tok ->toktype = 'a';
			cmd->input = push_intoarr(cmd->input, tok);
			free(tok->content);
			free(tok);
			piped_cmd->content = cmd;
		}
		node = node->next;
	}
}
