/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:19:48 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/15 20:09:42 by sadoming         ###   ########.fr       */
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
	return (cmd);
}

static t_list	*create_comand_behind(t_list *comands, t_cmd *cmd)
{
	t_list	*new_comand;
	t_cmd	*comand;

	comand = NULL;
	if (!ft_strllen(cmd->input))
		return (comands);
	if (cmd->input[0] == '\"' || cmd->input[0] == '\'')
		return (comands);
	if (!ft_strstr(cmd->input, " "))
		return (comands);
	comand = ft_calloc(sizeof(t_cmd), 1);
	if (!comand)
		return (comands);
	comand->options = ft_strdup(cmd->options);
	cmd->options = ft_free_str(cmd->options);
	comand->comand = ft_strdup(ft_strchr(cmd->input, ' ') + 1);
	comand->input = ft_strdup(ft_strchr(comand->comand, ' ') + 1);
	comand->comand = ft_strcut(comand->comand, ' ', '<', 'y');
	new_comand = ft_lstnew(comand);
	if (!new_comand)
		return (comands);
	new_comand->next = comands->next;
	comands->next = new_comand;
	return (comands);
}

t_list	*polish_comands(t_list *first, t_list *comands)
{
	t_cmd	*cmd;

	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (cmd->cmdtype == REDIR)
		{
			comands = create_comand_behind(comands, cmd);
			if (ft_strllen(cmd->input))
				if (!(cmd->input[0] == '\'' || cmd->input[0] == '\"'))
					cmd->input = ft_strcut(cmd->input, ' ', '<', 'y');
			if (comands->next)
			{
				cmd = (t_cmd *)comands->next->content;
				if (!ft_strllen(cmd->input))
					cmd->input = ft_free_str(cmd->input);
				cmd = asign_comandtype(cmd);
			}
		}
		cmd = quote_removal_comand(cmd);
		cmd = quote_removal_input(cmd);
		comands = comands->next;
	}
	return (first);
}
