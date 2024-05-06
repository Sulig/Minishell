/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_common_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:09 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/06 19:59:13 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_err_args(void)
{
	ft_printf_fd(2, Y);
	ft_printf_fd(2, "Please don't introduce arguments in ");
	ft_printf_fd(2, "minishell \nIt will not be interpreted\n");
	exit(1);
}

int	print_err_syntax(char *content)
{
	ft_printf_fd(2, "%s: syntax error near token", "minishell");
	if (!content)
		ft_printf_fd(2, " %cnewline'\n", 96);
	else
		ft_printf_fd(2, " %c%s'\n", 96, content);
	return (0);
}

int	print_comandnotfound(char *comand)
{
	ft_printf_fd(2, "%s: %s: ", "minishell", comand);
	ft_printf_fd(2, "command not found\n");
	return (127);
}

int	print_err_custom(char *error, int error_n)
{
	ft_printf_fd(2, "%s: An error ocurred!\n", "minishell");
	ft_printf_fd(2, "~ Info: %s\n", error);
	ft_printf_fd(2, D);
	return (error_n);
}

int	print_comun_error(char *error, int error_n)
{
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (error_n);
}
