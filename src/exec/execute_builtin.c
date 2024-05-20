/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:32:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 18:37:06 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prepare_echo(t_list *piped_cmd)
{
	t_cmd	*first_cmd;
	t_cmd	*cmd;

	first_cmd = piped_cmd->content;
	piped_cmd = piped_cmd->next;
	while (piped_cmd)
	{
		cmd = piped_cmd->content;
		if (cmd->cmdtype == CMD)
			first_cmd->input = cmd->comand;
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
	cmd = piped_cmd->content;
	if (!ft_strncmp(cmd->comand, "echo", 5) && tshell->cmd_size > 1)
		prepare_echo(piped_cmd);
	if (!ft_strncmp(cmd->comand, "cd", 3))
		ext_stat = builtin_cd(cmd, tshell->env);
	else if (!ft_strncmp(cmd->comand, "echo", 5))
		ext_stat = builtin_echo(cmd);
	else if (!ft_strncmp(cmd->comand, "env", 4))
		ext_stat = builtin_env(tshell->env);
	else if (!ft_strncmp(cmd->comand, "exit", 5))
		ext_stat = builtin_exit(cmd, ext_stat, is_child);
	else if (!ft_strncmp(cmd->comand, "export", 7))
		ext_stat = builtin_export(cmd, tshell);
	else if (!ft_strncmp(cmd->comand, "pwd", 4))
		ext_stat = builtin_pwd();
	else if (!ft_strncmp(cmd->comand, "unset", 6))
		ext_stat = builtin_unset(cmd, tshell->env);
	return (ext_stat);
}
