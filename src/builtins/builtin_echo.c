/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:56:45 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:03:19 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_flag(char *word)
{
	if (word[0] == '-' && word[0] == 'n' && ft_strllen(word) == 2)
		return (TRUE);
	else
		return (FALSE);
}

// Output the 'args', separated by spaces, followed by a newline.
// The return status is always 0.
// If -n is specified, the trailing newline is suppressed.
int	builtin_echo(t_cmd *cmd)
{
	int	flag;

	flag = FALSE;
	if (cmd->options)
		flag = check_flag(cmd->options);
	if (!flag && cmd->options)
	{
		printf("%s", cmd->options);
		if (cmd->input != NULL)
			printf(" ");
	}
	if (cmd->input != NULL)
		ft_putstr_fd(cmd->input, STDOUT_FILENO);
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
