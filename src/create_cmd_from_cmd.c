/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_from_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:19:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/13 19:39:54 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void create_false_cmd(t_cmd *cmd)
{
	char	*echo;
	char	*option;

	echo = "echo";
	option = "-n";
	free(cmd->comand);
	free(cmd->options);
	free(cmd->input);
	cmd->comand = ft_strdup(echo);
	cmd->options = ft_strdup(option);
	cmd->input = NULL;
}

void	create_cmd_from_cmd(t_shell *tshell)
{
	t_list	*cmds;
	t_cmd	*comand;
	char	**args;


	cmds = tshell->comands;
	while (cmds)
	{
		comand = cmds->content;
		if (comand->comand != NULL && comand->comand[0] == '$')
		{
			if (ft_strlen(comand->comand) > 1)
			{
				if(comand->input != NULL)
				{
					args = ft_split(comand->input, ' ');
					free(comand->comand);
					free(comand->input);
					comand->comand = ft_strdup(args[0]);
					comand->input = ft_strdup(args[1]); //Concatenar los args que queden
					free_arr_2d(args);
				}
				else
				{
					create_false_cmd(comand);
				}
			}
		}
		cmds = cmds->next;
	}
}
