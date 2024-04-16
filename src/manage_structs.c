/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:47:15 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 19:44:31 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_get_pid()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(print_err_custom(MERR_FORK, 1));
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}

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
			cmd->comand = ft_free_str(cmd->comand);
			cmd->options = ft_free_str(cmd->options);
			cmd->input = ft_free_str(cmd->input);
			tmp = tmp->next;
		}
	}
	ft_lstclear(&tshell->comands, free);
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
	if (!ft_arr_strlen(tshell->path))
		return (free_tshell(tshell));
	tshell->line = NULL;
	tshell->tokens = NULL;
	tshell->comands = NULL;
	tshell->tok_size = 0;
	tshell->cmd_size = 0;
	return (tshell);
}
