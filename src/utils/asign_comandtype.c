/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_comandtype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/03 16:47:54 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*quote_removal(t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strtrim_s(cmd->input, "\"");
	cmd->input = ft_strremplace(cmd->input, tmp);
	tmp = ft_free_str(tmp);
	tmp = ft_strtrim_s(cmd->input, "\'");
	cmd->input = ft_strremplace(cmd->input, tmp);
	tmp = ft_free_str(tmp);
	return (cmd);
}

t_cmd	*asign_comandtype(t_cmd *cmd)
{
	if (cmd->cmdtype == PIPE)
		return (cmd);
	if (cmd->cmdtype == REDIR)
	{
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
	cmd = quote_removal(cmd);
	return (cmd);
}
