/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:44:25 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:02:04 by jguillot         ###   ########.fr       */
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
		if (ft_strchr(cmd->input, ' ') == NULL)
			return (print_err_syntax("exit: too many arguments"));
		else if (!ft_isnumeric(cmd->input))
			return (print_err_syntax("exit: numeric argument required"));
		else
			exit_status = ft_atoi(cmd->input);
	}
	while (exit_status >= 256)
		exit_status = exit_status - 256;
	printf("exit\n");
	exit(exit_status);
	return (exit_status);
}
