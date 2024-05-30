/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:23:34 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 16:51:04 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Executes the command 'cmd' (which might be a builtin) assuming there are no
// redirections and exits with the appropriate exit status.
void	execute_command(t_list *cmds, t_shell *tshell)
{
	int		exit_stat;
	t_cmd	*cmd;
	t_list	*node;

	node = cmds;
	while (node)
	{
		cmd = node->content;
		if (cmd->cmdtype != REDIR)
		{
			set_signals(NON_INTER);
			if (cmd->cmdtype == TNULL)
				exit(EXIT_SUCCESS);
			if (is_builtin_name(cmd))
			{
				exit_stat = execute_builtin(cmds, tshell, TRUE);
				exit(exit_stat);
			}
			exec_cmd(cmd, tshell->env);
		}
		node = node->next;
	}
	exit(EXIT_FAILURE);
}
