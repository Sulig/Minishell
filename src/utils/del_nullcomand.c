/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_nullcomand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:23:28 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 20:17:57 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*lst_delone(t_list *node)
{
	t_list	*prev;
	t_list	*next;

	if (!node)
		return (NULL);
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (node->content)
		free(node->content);
	free(node);
	node = NULL;
	return (next);
}

t_list	*del_nullcomand(t_list *first, t_list *comands)
{
	t_cmd	*cmd;
	size_t	cmd_size;

	cmd_size = ft_lstsize(first);
	//In progress, this will need to free the original
	if (cmd_size == 1)
		first = lst_delone(first);
	while (comands && cmd_size)
	{
		cmd = (t_cmd *)comands->content;
		if (!ft_strllen(cmd->comand))
		{
			cmd->options = ft_free_str(cmd->options);
			cmd->input = ft_free_str(cmd->input);
			comands = lst_delone(comands);
			cmd_size--;
		}
		if (comands)
			comands = comands->next;
	}
	if (!cmd_size)
	{
		ft_lstclear(&first, free);
		return (NULL);
	}
	return (first);
}
