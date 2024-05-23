/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_nullcomands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:14:12 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/23 20:03:37 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*destroy_nullcomands(t_shell *tshell, t_list *first, t_list *comands)
{
	t_cmd	*cmd;

	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (!ft_strllen(cmd))
		{
			cmd->comand = ft_free_str(cmd->comand);
			cmd->options = ft_free_str(cmd->options);
			cmd->input = ft_free_str(cmd->input);
			if (tshell->cmd_size == 1)
			{
				ft_lstclear(&tshell->comands, free);
				return (NULL);
			}
			if (!comands->next)
			{
				comands->prev->next = NULL;
				free(comands);
				break ;
			}
			//gestionar caso de que si haya siguiente
		}
		comands = comands->next;
	}
	return (first);
}
