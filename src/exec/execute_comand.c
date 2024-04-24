/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:23:34 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 17:51:20 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Executes the command 'cmd' (which might be a builtin) assuming there are no
// redirections and exits with the appropriate exit status.
void	execute_command(t_list *cmds, int exit_status, char **env)
{
	int		exit_stat;
	char	*args;
	char	**e;
	t_cmd 	*cmd;

	cmd = cmds->content;
	//set_signals(NON_INTER);

	if (cmd->cmdtype == TNULL)
		exit(EXIT_SUCCESS);
	if (is_builtin_name(cmd->comand))
	{
		e = arrstr_dup(env);
		exit_stat = execute_builtin(cmds, exit_status, &e, TRUE);
		arrstr_free(e);
		exit(exit_stat);
	}
	exec_cmd(cmd, env);
	exit(EXIT_FAILURE);
}
