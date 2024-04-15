/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:47:46 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/15 20:09:49 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin_name(t_cmd *cmd)
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
	if (cmd->cmdtype == PIPE || cmd->cmdtype == REDIR)
		return (0);
	else if (is_builtin_name(cmd))
		return (0);
	else if (ft_strstr(cmd->comand, "./"))
		return (0);
	while (cmd->comand[i])
	{
		if (!ft_isalnum(cmd->comand[i]))
			return (print_comandnotfound(cmd->comand));
		i++;
	}
	if (access(cmd->comand, X_OK) == 0 || access(cmd->comand, W_OK))
		return (0);
	return (print_comandnotfound(cmd->comand));
}

void	find_comands(t_shell *tshell, t_list *comands)
{
	t_cmd	*cmd;

	get_set_path(tshell);
	if (!tshell->path)
	{
		tshell->exit_state = print_err_custom("No PATH finded");
		return ;
	}
	if (access(tshell->path, R_OK) == -1)
	{
		tshell->exit_state = print_err_custom("Can't access to PATH");
		return ;
	}
	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		tshell->exit_state = checkif_comandexist(cmd);
		if (tshell->exit_state != 0)
			cmd->comand = ft_free_str(cmd->comand);
		comands = comands->next;
	}
}
