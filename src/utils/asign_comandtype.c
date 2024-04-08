/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_comandtype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/08 18:22:47 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*quote_removal_comand(t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strllen(cmd->comand))
			return (cmd);
	if (cmd->comand[0] == '\"')
	{
		tmp = ft_strtrim_s(cmd->comand, "\"");
		cmd->comand = ft_strremplace(cmd->comand, tmp);
	}
	else if (cmd->comand[0] == '\'')
	{
		tmp = ft_strtrim_s(cmd->comand, "\'");
		cmd->comand = ft_strremplace(cmd->comand, tmp);
	}
	tmp = ft_free_str(tmp);
	if (!ft_strllen(cmd->comand))
		cmd->comand = ft_free_str(cmd->comand);
	return (cmd);
}

t_cmd	*quote_removal_input(t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strllen(cmd->input))
			return (cmd);
	if (cmd->input[0] == '\"')
	{
		tmp = ft_strtrim_s(cmd->input, "\"");
		cmd->input = ft_strremplace(cmd->input, tmp);
	}
	else if (cmd->input[0] == '\'')
	{
		tmp = ft_strtrim_s(cmd->input, "'");
		cmd->input = ft_strremplace(cmd->input, tmp);
	}
	tmp = ft_free_str(tmp);
	if (!ft_strllen(cmd->input))
		cmd->input = ft_free_str(cmd->input);
	return (cmd);
}

t_cmd	*asign_comandtype(t_cmd *cmd)
{
	if (cmd->cmdtype == PIPE)
		return (cmd);
	if (my_strcmp("<", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">>", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp("<<", cmd->comand))
		cmd->cmdtype = REDIR;
	else
		cmd->cmdtype = CMD;
	cmd = quote_removal_comand(cmd);
	cmd = quote_removal_input(cmd);
	return (cmd);
}
