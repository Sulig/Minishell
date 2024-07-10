/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:28:49 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/25 15:49:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->name->content, "") || cmd->name->content[0] == '\0')
	{
		if (cmd->input && cmd->input[0])
		{
			free(cmd->name->content);
			cmd->name->content = ft_strdup(cmd->input[0]->content);
			cmd->input = pop_outarr(cmd->input, 0);
			if (cmd->input[0] && (ft_strcmp(cmd->input[0]->content, "")
					|| cmd->input[0]->content[0] == '\0'))
				cmd->input = pop_outarr(cmd->input, 0);
		}
		else
			return (0);
	}
	return (1);
}

int	check_comand(t_shell *tshell)
{
	int		i;
	int		j;
	t_cmd	*cmd;
	int		stat;

	i = 0;
	while (tshell->tree_cmd && tshell->tree_cmd[i])
	{
		j = 0;
		while (tshell->tree_cmd[j] && tshell->tree_cmd[j]->content)
		{
			cmd = tshell->tree_cmd[j]->content;
			stat = check_cmd(cmd);
			if (!stat)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
