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
