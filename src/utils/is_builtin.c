/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:46:52 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 18:16:59 by sadoming         ###   ########.fr       */
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
