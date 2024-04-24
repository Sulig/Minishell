/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:32:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 17:09:31 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Executes the builtin defined by 'cmd'
 * assuming there are no redirections and modifying the 'env' if required.
 * The 'child' flag indicates if we're on a child process.
 * Returns the exit status.
*/
int	execute_builtin(t_list *piped_cmd, int exit_status, char **env, int is_child)
{
	t_cmd *cmd;

	cmd = piped_cmd->content;
	(void)is_child;
    if (!ft_strncmp(cmd->comand, "cd", 3))
		exit_status = builtin_cd(cmd, env);
	else if (!ft_strncmp(cmd->comand, "echo", 5))
		exit_status = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->comand, "env", 4))
		exit_status = builtin_env(env);
	else if (!ft_strncmp(cmd->comand, "exit", 5))
		exit_status = builtin_exit(cmd);
	else if (!ft_strncmp(cmd->comand, "export", 7))
		exit_status = builtin_export(cmd, env);
	else if (!ft_strncmp(cmd->comand, "pwd", 4))
		exit_status = builtin_pwd();
	else if (!ft_strncmp(cmd->comand, "unset", 6))
		exit_status = builtin_unset(cmd, env);
	return (exit_status);
}
