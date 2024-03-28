/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_comandtype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/28 19:58:03 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*asign_comandtype(t_cmd *cmd)
{
	if (cmd->cmdtype == PIPE)
		return (cmd);
	if (cmd->cmdtype == REDIR)
	{
		ft_printf("asign filename to output!\n");
		cmd->output = ft_strdup(cmd->input);
		cmd->input = ft_free_str(cmd->input);
	}
	if (my_strcmp("<", cmd->comand))
		cmd->cmdtype = REDIR_IN;
	else if (my_strcmp(">", cmd->comand))
		cmd->cmdtype = REDIR_OUT;
	else if (my_strcmp(">>", cmd->comand))
		cmd->cmdtype = REDIR_APP;
	else if (my_strcmp("<<", cmd->comand))
		cmd->cmdtype = REDIR_DEL;
	else
		cmd->cmdtype = CMD;
	return (cmd);
}
