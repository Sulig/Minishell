/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_comandtype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/11 17:07:18 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Remove the quotes of the comand name
 * if the first type of quote is \"
 * remove only \"
 * if the first type of quote is \'
 * remove only \'
 * So, in case of "''" -> ''
 * in case of '""' -> ""
*/
static t_cmd	*quote_removal_comand(t_cmd *cmd)
{
	char	*tmp;
	size_t	dq_pos;
	size_t	sq_pos;

	tmp = NULL;
	if (!ft_strllen(cmd->comand))
		return (cmd);
	dq_pos = ft_cnttoch_out(cmd->comand, '\"');
	sq_pos = ft_cnttoch_out(cmd->comand, '\'');
	if (dq_pos == sq_pos)
		return (cmd);
	else if (dq_pos < sq_pos)
	{
		tmp = ft_strtrim_inside(cmd->comand, '\"');
		cmd->comand = ft_strremplace(cmd->comand, tmp);
	}
	else if (sq_pos < dq_pos)
	{
		tmp = ft_strtrim_inside(cmd->comand, '\'');
		cmd->comand = ft_strremplace(cmd->comand, tmp);
	}
	tmp = ft_free_str(tmp);
	if (!ft_strllen(cmd->comand))
		cmd->comand = ft_free_str(cmd->comand);
	return (cmd);
}

/*
 * Remove the quotes of the comand name
 * if the first type of quote is \"
 * remove only \"
 * if the first type of quote is \'
 * remove only \'
 * So, in case of "''" -> ''
 * in case of '""' -> ""
*/
static t_cmd	*quote_removal_input(t_cmd *cmd)
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

/*
 * Asing comand type:
 * - REDIR	< << > >>
 * - PIPE	|
 * - CMD	the rest...
 *
 * And do:
 * * Quote removal of comand
 * * Trim the input & quote removal
*/
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
