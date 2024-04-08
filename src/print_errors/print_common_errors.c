/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_common_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:09 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/08 19:03:29 by sadoming         ###   ########.fr       */
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
	else if (my_strcmp(content, "|"))
		ft_printf_fd(2, " %c%s'\n", 96, content);
	else
		ft_printf_fd(2, " %c%s'\n", 96, content);
	return (0);
}

int	print_comandnotfound(char *comand)
{
	ft_printf_fd(2, "%s: %s: ", "minishell", comand);
	ft_printf_fd(2, "comand not found\n");
	return (127);
}

int	print_err_custom(char *error)
{
	ft_printf_fd(2, R);
	ft_printf_fd(2, "%s: An error ocurred!\n", "minishell");
	ft_printf_fd(2, "~ Info: %s\n", error);
	ft_printf_fd(2, D);
	return (127);
}
