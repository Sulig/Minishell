/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:32:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:11:18 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Executes the builtin defined by 'cmd'
 * assuming there are no redirections and modifying the 'env' if required.
 * The 'child' flag indicates if we're on a child process.
 * Returns the exit status.
*/
int	execute_builtin(t_list *piped_cmd, int ext_stat, char **env, int is_child)
{
	t_cmd	*cmd;

	cmd = piped_cmd->content;
	(void)is_child;
	if (!ft_strncmp(cmd->comand, "cd", 3))
		ext_stat = builtin_cd(cmd, env);
	else if (!ft_strncmp(cmd->comand, "echo", 5))
		ext_stat = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->comand, "env", 4))
		ext_stat = builtin_env(env);
	else if (!ft_strncmp(cmd->comand, "exit", 5))
		ext_stat = builtin_exit(cmd);
	else if (!ft_strncmp(cmd->comand, "export", 7))
		ext_stat = builtin_export(cmd, env);
	else if (!ft_strncmp(cmd->comand, "pwd", 4))
		ext_stat = builtin_pwd();
	else if (!ft_strncmp(cmd->comand, "unset", 6))
		ext_stat = builtin_unset(cmd, env);
	return (ext_stat);
}
