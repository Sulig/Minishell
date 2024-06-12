/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:28:49 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:29:11 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin(const char *str)
{
	if (!ft_strncmp(str, "cd", 3) || !ft_strncmp(str, "echo", 5) || \
	!ft_strncmp(str, "env", 4) || !ft_strncmp(str, "exit", 5) || \
	!ft_strncmp(str, "export", 7) || !ft_strncmp(str, "pwd", 4) || \
	!ft_strncmp(str, "unset", 6))
		return (TRUE);
	return (FALSE);
}

int	is_builtin_cmd(t_list *cmd_lst)
{
	t_list	*node;
	t_cmd	*cmd;

	node = cmd_lst;
	if (node)
	{
		cmd = node->content;
		while (cmd->cmdtype == REDIR)
		{
			node = node->next;
			if (!node)
				return (FALSE);
			cmd = node->content;
		}
		if (!ft_strllen(cmd->comand))
			return (FALSE);
		if (is_builtin(cmd->comand))
			return (TRUE);
	}
	return (FALSE);
}
