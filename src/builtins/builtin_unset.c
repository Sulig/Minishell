/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:37:01 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 19:10:28 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_unset(t_cmd *cmd, t_shell *tshell)
{
	int		i;
	int		exit_status;
	char	**args;

	exit_status = 0;
	if (cmd->input != NULL)
	{
		i = 0;
		args = get_arr_input_from_cmd(cmd);
		if (!ft_arr_strlen(args))
		{
			free_arr_2d(args);
			return (0);
		}
		while (args[i])
		{
			if (env_valid_varname(args[i]))
				remove_env_var(args[i], tshell);
			else
				exit_status = print_err_custom(MERR_UNSET, 127);
			i++;
		}
		free_arr_2d(args);
	}
	return (exit_status);
}
