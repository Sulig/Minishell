/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intodoublelist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:41:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/13 17:05:03 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	search_pipes(t_list *comands)
{
	t_cmd	*cmd;
	size_t	pipes;

	pipes = 1;
	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (cmd->cmdtype == PIPE)
			pipes++;
		comands = comands->next;
	}
	return (pipes);
}

/*
 * Save the list with the Xcmd cmd to | or NULL
 * *Don't include the '|'
 * And include this list into a double list.
 * Exemple:
 * [0][ CMD - REDIR - CMD ]
 * [1][ CMD ]
*/
static t_list	*create_nodelist_intodll(t_list *cmds)
{
	static size_t	comand;
	t_list			*list;
	t_list			*tmp;
	t_cmd			*cmd;

	list = NULL;
	cmds = ft_lstgetnode(cmds, comand);
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		if (cmd->cmdtype == PIPE)
			break ;
		tmp = ft_lstnew(cmd);
		ft_lstadd_back(&list, tmp);
		cmds = cmds->next;
	}
	comand = ft_lstsize(cmds);
	if (cmds)
		comand = cmds->pos + 1;
	return (list);
}

/*
 * Converts the list of comands into a double list.
 * Each Position into **multiple_cmd can be diferent cmds & redirs
 * The size of this array is calculated by number of PIPES + 1
*/
void	split_intodoublelist(t_shell *tshell)
{
	t_list	**multiple_cmd;
	size_t	nodes;
	size_t	pos;

	multiple_cmd = NULL;
	if (!tshell->comands || !tshell->cmd_size)
		return ;
	nodes = search_pipes(tshell->comands);
	multiple_cmd = ft_calloc(sizeof(t_list **), nodes + 1);
	if (!multiple_cmd)
	{
		tshell->exit_state = print_err_custom(MERR_MALLOC, 1);
		return ;
	}
	pos = 0;
	while (pos < nodes)
	{
		multiple_cmd[pos] = create_nodelist_intodll(tshell->comands);
		pos++;
	}
	tshell->tree_cmd = multiple_cmd;
}
