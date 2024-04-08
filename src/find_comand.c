/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:47:46 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/08 17:05:34 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_in_builtin(t_cmd *cmd)
{
    if (my_strcmp("echo", cmd->comand))
		return (1);
	if (my_strcmp("cd", cmd->comand))
		return (1);
	if (my_strcmp("pwd", cmd->comand))
		return (1);
	if (my_strcmp("export", cmd->comand))
		return (1);
	if (my_strcmp("unset", cmd->comand))
		return (1);
	if (my_strcmp("env", cmd->comand))
		return (1);
	if (my_strcmp("exit", cmd->comand))
		return (1);
	return (0);
}

static int	checkif_comandexist(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (!ft_strllen(cmd->comand))
	{
		if (ft_strllen(cmd->input))
			return (print_comandnotfound(""));
		return (0);
	}
	if (find_in_builtin(cmd))
		return (0);
	while (cmd->comand[i])
	{
		if (cmd->cmdtype == PIPE)
			return (0);
		if (ft_strchr(cmd->comand, '>') || ft_strchr(cmd->comand, '<'))
			return (0);
		if (!ft_is_alphanumeric(cmd->comand[i]))
			return (print_comandnotfound(cmd->comand));
		i++;
	}
	//The comand it is searched in system??
	//Search next day
	return (print_comandnotfound(cmd->comand));
}

void	find_comands(t_shell *tshell, t_list *comands)
{
	while (comands)
	{
		tshell->exit_state = checkif_comandexist((t_cmd *)comands->content);
		comands = comands->next;
	}
	ft_printf("Reached end of comands\n");
}
