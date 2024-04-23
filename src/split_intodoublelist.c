/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intodoublelist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:41:05 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/23 20:03:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	search_pipes(t_list *comands)
{
	t_cmd	*cmd;
	size_t	pipes;

	pipes = 0;
	while (comannds)
	{
		cmd = (t_cmd *)comands->cotent;
		if (cmd->cmdtype == PIPE)
			pipes++;
		comands = comands->next;
	}
	return (pipes);
}

//void create_nodelist_intodll(t_list *cmds, t_list ***mlt_cmds, size_t nodes)
//{
//	size_t	pos;
//	t_list	*tmp;
//	t_cmd	*cmd;
//
//	pos = 0;
//	while ()
//	{
//		//pos++?
//		//Create nodelist
//		//Create *tmp cmd->content hasta |
//		//*mlt_cmds[pos] = ft_lstnew(tmp);
//		//cmds = cmds->next??
//	}
//}

void	split_intodoublelist(t_shell *tshell)
{
	t_list	**mutiple_cmd;
	size_t	nodes;

	multiple_cmd = NULL;
	if (!tshell->comands || !tshell->cmd_size)
		return ;
	nodes = search_pipes(tshell->comands);
	multiple_cmd = ft_calloc(sizeof(t_list *), nodes + 1);
	if (!multiple_cmd)
	{
		tshell->exit = print_custom(MERR_MALLOC, 1);
		return ;
	}
	//create node-list inside multiple_cmd
	//create_nodelist_intodll(tshell->comands, &multiple_cmd, nodes);
}
