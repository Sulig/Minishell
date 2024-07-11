/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:28:49 by jguillot          #+#    #+#             */
/*   Updated: 2024/07/11 10:00:51 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(t_cmd *cmd)
{
	if (!ft_strllen(cmd->name->content))
	{
		if (len_of_tokens(cmd->input))
		{
			cmd->name->content = ft_free_str(cmd->name->content);
			cmd->name->content = ft_strdup(cmd->input[0]->content);
			cmd->input = pop_outarr(cmd->input, 0);
			if (!len_of_tokens(cmd->input))
				cmd->input = clear_tarr(cmd->input);
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
