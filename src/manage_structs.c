/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:47:15 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/28 17:37:21 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_shell *tshell)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tshell->tokens;
	if (tshell->tokens)
	{
		while (tshell->tok_size--)
		{
			token = (t_token *)tmp->content;
			token->content = ft_free_str(token->content);
			tmp = tmp->next;
		}
		tshell->tok_size = 0;
	}
	ft_lstclear(&tshell->tokens, free);
}

void	free_comands(t_shell *tshell)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = tshell->comands;
	if (tshell->cmd_size)
	{
		while (tshell->cmd_size--)
		{
			cmd = (t_cmd *)tmp->content;
			cmd->name->content = ft_free_str(cmd->name->content);
			cmd->flags = clear_tarr(cmd->flags);
			cmd->input = clear_tarr(cmd->input);
			tmp = tmp->next;
		}
		tshell->cmd_size = 0;
	}
	ft_lstclear(&tshell->comands, free);
}

void	free_tree_cmds(t_shell *tshell)
{
	size_t	pos;

	pos = 0;
	if (!tshell->tree_cmd)
		return ;
	while (tshell->tree_cmd[pos])
	{
		ft_lstclear(&tshell->tree_cmd[pos], donothing);
		tshell->tree_cmd[pos] = NULL;
		pos++;
	}
	free(tshell->tree_cmd);
	tshell->tree_cmd = NULL;
}

void	*free_tshell(t_shell *tshell)
{
	if (!tshell)
		return (NULL);
	tshell->env = ft_auto_free_arr(tshell->env);
	tshell->path = ft_auto_free_arr(tshell->path);
	tshell->line = ft_free_str(tshell->line);
	if (tshell->tokens && tshell->tok_size)
		free_tokens(tshell);
	if (tshell->comands && tshell->cmd_size)
		free_comands(tshell);
	if (tshell->tree_cmd)
		ft_lstclear(tshell->tree_cmd, free);
	free(tshell);
	return (NULL);
}

t_shell	*init_tshell(t_shell *tshell, char **env)
{
	tshell = ft_calloc(sizeof(t_shell), 1);
	if (!tshell)
		return (NULL);
	tshell->exit_state = 0;
	tshell->env = ft_strarrdup(env);
	if (!tshell->env)
		return (free_tshell(tshell));
	set_path(tshell);
	tshell->line = NULL;
	tshell->tokens = NULL;
	tshell->comands = NULL;
	tshell->tok_size = 0;
	tshell->cmd_size = 0;
	return (tshell);
}
