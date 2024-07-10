/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:32:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/25 15:49:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	prepare_echo_old(t_list *piped_cmd)
{
	t_cmd	*first_cmd;
	t_cmd	*cmd;

	first_cmd = piped_cmd->content;
	piped_cmd = piped_cmd->next;
	while (piped_cmd)
	{
		cmd = piped_cmd->content;
		if (cmd->cmdtype == CMD)
		{
			first_cmd->input[0]->content = NULL;
			first_cmd->input[0]->content = ft_strdup(cmd->name->content);
		}
		piped_cmd = piped_cmd->next;
	}
}

/*
 * Executes the builtin defined by 'cmd'
 * assuming there are no redirections and modifying the 'env' if required.
 * The 'child' flag indicates if we're on a child process.
 * Returns the exit status.
*/
int	execute_builtin(t_list *piped_cmd, t_shell *tshell, int is_child)
{
	t_cmd	*cmd;
	int		ext_stat;

	ext_stat = tshell->exit_state;
	cmd = dobefore_execve(tshell, piped_cmd->content);
	if (!ft_strncmp(cmd->name->content, "echo", 5) && tshell->cmd_size > 1)
		prepare_echo(piped_cmd);
	if (!ft_strncmp(cmd->name->content, "cd", 3))
		ext_stat = builtin_cd(cmd, tshell);
	else if (!ft_strncmp(cmd->name->content, "echo", 5))
		ext_stat = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->name->content, "env", 4))
		ext_stat = builtin_env(tshell->env);
	else if (!ft_strncmp(cmd->name->content, "exit", 5))
		ext_stat = builtin_exit(cmd, ext_stat, is_child);
	else if (!ft_strncmp(cmd->name->content, "export", 7))
		ext_stat = builtin_export(cmd, tshell);
	else if (!ft_strncmp(cmd->name->content, "pwd", 4))
		ext_stat = builtin_pwd();
	else if (!ft_strncmp(cmd->name->content, "unset", 6))
		ext_stat = builtin_unset(cmd, tshell);
	return (ext_stat);
}
