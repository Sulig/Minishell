/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:56:45 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/27 18:19:37 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_flag(char *word)
{
	int	i;

	i = 0;
	if (word[i++] != '-')
		return (FALSE);
	while (word[i] && word[i] == 'n')
		++i;
	if (word[i])
		return (FALSE);
	return (TRUE);
}

static int	get_flag(char **args)
{
	int	idx;

	idx = 0;
	while (args[idx] && is_flag(args[idx]))
		++idx;
	return (idx);
}

// Output the 'args', separated by spaces, followed by a newline.
// The return status is always 0.
// If -n is specified, the trailing newline is suppressed.
int	builtin_echo(t_cmd *cmd)
{
	int		flag;
	char	**args;

	flag = FALSE;
	if (cmd->options)
	{
		args = ft_split(cmd->options, ' ');
		flag = get_flag(args);
		free_arr_2d(args);
	}
	if (cmd->input != NULL)
		ft_putstr_fd(cmd->input, STDOUT_FILENO);
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
