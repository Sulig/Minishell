/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/17 20:01:57 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*quote_removal_comand(t_cmd *cmd)
{
	char	*tmp;
	char	to_remove;
	size_t	pos_dq;
	size_t	pos_sq;

	tmp = NULL;
	to_remove = '\0';
	if (!cmd->comand)
		return (cmd);
	if (!ft_strchr(cmd->comand, '\"') && !ft_strchr(cmd->comand, '\''))
		return (cmd);
	pos_dq = ft_cnt_tostr(cmd->comand, "\"");
	pos_sq = ft_cnt_tostr(cmd->comand, "\'");
	if (pos_dq < pos_sq)
		to_remove = '\"';
	else if (pos_sq < pos_dq)
		to_remove = '\'';
	tmp = ft_strtrim_inside(cmd->comand, to_remove);
	ft_printf("\n\033[1;36m Result: %s\n\033[0;37m\n", tmp);
	return (cmd);
}
