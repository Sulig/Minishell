/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:32:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 18:48:40 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Executes the builtin defined by 'cmd' assuming there are no redirections and
// modifying the 'env' if required.
// The 'child' flag indicates if we're on a child process.
// Returns the exit status.
int	execute_builtin(t_cmd *cmd, int exit_status, char **env, int is_child)
{
    if (!ft_strncmp(cmd->comand, "cd", 3))
		exit_status = 0;//cd_builtin(cmd, *env);
	else if (!ft_strncmp(cmd->comand, "echo", 5))
		exit_status = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->comand, "env", 4))
		exit_status = 0;//env_builtin(*env);
	else if (!ft_strncmp(cmd->comand, "exit", 5))
		exit_status = 0;//exit_builtin(cmd, exit_status, is_child);
	else if (!ft_strncmp(cmd->comand, "export", 7))
		exit_status = 0;//export_builtin(cmd, env);
	else if (!ft_strncmp(cmd->comand, "pwd", 4))
		exit_status = builtin_pwd();
	else if (!ft_strncmp(cmd->comand, "unset", 6))
		exit_status = 0;//unset_builtin(cmd, env);
	return (exit_status);
}