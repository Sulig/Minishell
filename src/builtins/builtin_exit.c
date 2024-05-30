/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:44:25 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/23 12:00:35 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_llong(char *arg)
{
	int		len;
	int		diff;
	char	sign;

	sign = '+';
	if (*arg == '-' || *arg == '+')
	{
		sign = *arg;
		arg++;
	}
	while (*arg == '0')
		arg++;
	len = ft_strlen(arg);
	if (len > 19)
		return (FALSE);
	if (len == 19)
	{
		if (sign == '-')
			diff = ft_strncmp(arg, LLINT_MIN_STR, 19);
		else
			diff = ft_strncmp(arg, LLINT_MAX_STR, 19);
		if (diff > 0)
			return (FALSE);
	}
	return (TRUE);
}
// Long long range: -9223372036854775808 > 9223372036854775807

static int	is_longlong(char *arg)
{
	int	i;

	i = 0;
	if (!*arg)
		return (FALSE);
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i + 1] == 0)
			return (FALSE);
		++i;
	}
	while (arg[i] == '0')
		++i;
	while (arg[i] && ((arg[i] <= '9' && arg[i] >= '0')))
		++i;
	if (arg[i])
		return (FALSE);
	return (ft_check_llong(arg));
}

/*
handles more than 2 arguments
handles no arguments exiting with code 0
handles non numeric arguments
handles arguments with values larger than 255 (max exit code)
*/
int	builtin_exit(t_cmd *cmd, int exit_status, int is_child)
{
	int		exit_stat;
	char	*arg;

	if (!is_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->input == NULL && cmd->options == NULL)
		restore_exit(exit_status);
	if (cmd->input != NULL && cmd->options != NULL)
		return (print_comun_error("too many arguments", 1));
	if (cmd->options != NULL)
		cmd->input = ft_strdup(cmd->options);
	if (ft_strchr(cmd->input, ' ') != NULL)
		return (print_comun_error("too many arguments", 1));
	arg = ft_strtrim(cmd->input, " \n\t\v\f\r");
	if (is_longlong(arg) == FALSE)
	{
		free(arg);
		restore_exit(print_comun_error("numeric argument required", 2));
	}
	exit_stat = ft_atoll(arg);
	free(arg);
	restore_exit(exit_stat % 256);
	free(arg);
	return (exit_status);
}
