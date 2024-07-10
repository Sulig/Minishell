/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:23:34 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:27:12 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_command(t_list *cmds, t_shell *tshell)
{
	int		exit_stat;
	t_cmd	*cmd;
	t_list	*node;

	node = cmds;
	while (node)
	{
		cmd	= dobefore_execve(tshell, node->content);
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
