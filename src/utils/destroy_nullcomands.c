/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_nullcomands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:14:12 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/24 17:27:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*destroy_nullcomands(t_shell *tshell, t_list *first, t_list *comands)
{
	t_cmd	*cmd;

	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (!ft_strllen(cmd->comand))
		{
			cmd->comand = ft_free_str(cmd->comand);
			cmd->options = ft_free_str(cmd->options);
			cmd->input = ft_free_str(cmd->input);
			if (comands->prev)
				comands->prev->next = comands->next;
			if (comands->next)
				comands->next->prev = comands->prev;
			free(comands);

		}
		comands = comands->next;
	}
	if (!ft_lstsize(tshell->comands))
	{
		ft_lstclear(&tshell->comands, free);
		return (NULL);
	}
	return (first);
}
