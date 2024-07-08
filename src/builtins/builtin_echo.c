/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:56:45 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/25 15:59:52 by sadoming         ###   ########.fr       */
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

static int	get_flag(t_token **args)
{
	int	idx;

	idx = 0;
	if (!args)
		return (0);
	while (args[idx]->content && is_flag(args[idx]->content))
		++idx;
	return (idx);
}

int	builtin_echo(t_cmd *cmd)
{
	int		flag;

	flag = FALSE;
	// Search and recover the flags?
	if (cmd->flags)
		flag = get_flag(cmd->flags);
	if (cmd->input != NULL)
		ft_putstr_fd(cmd->input[0]->content, STDOUT_FILENO);
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
