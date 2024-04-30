/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:44:25 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/30 19:27:50 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
handles more than 2 arguments
handles no arguments exiting with code 0
handles non numeric arguments
handles arguments with values larger than 255 (max exit code)
*/
int	builtin_exit(t_cmd *cmd)
{
	int		exit_status;

	if (cmd->input == NULL)
		exit_status = 0;
	else
	{
		if (ft_strchr(cmd->input, ' ') != NULL)
			return (print_comun_error("too many arguments", 1));
		else if (!ft_isnumeric(cmd->input))
			return (print_comun_error("numeric argument required", 255));
		else
			exit_status = ft_atoi(cmd->input);
	}
	printf("exit\n");
	exit(exit_status % 256);
	return (exit_status);
}
