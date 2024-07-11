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
	while (args[idx] && args[idx]->content && is_flag(args[idx]->content))
		++idx;
	return (idx);
}

void	print_echo(t_cmd *cmd, int flag)
{
	int	i;
	int	notfirst;

	notfirst = FALSE;
	i = 0;
	if (cmd->input != NULL)
	{
		while (cmd->input[i])
		{
			if (notfirst)
				ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(cmd->input[i]->content, STDOUT_FILENO);
			notfirst = TRUE;
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtin_echo(t_cmd *cmd)
{
	int	flag;
	int	len;
	int	i;

	flag = FALSE;
	len = 0;
	i = flag;
	if (cmd->flags)
	{
		len = count_tokens(cmd->flags);
		flag = get_flag(cmd->flags);
		i = flag;
	}
	if (flag < len)
	{
		while (cmd->flags[i])
		{
			ft_putstr_fd(cmd->flags[i]->content, STDOUT_FILENO);
			if (i < len - 1 || cmd->input != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
	}
	print_echo(cmd, flag);
	return (0);
}
