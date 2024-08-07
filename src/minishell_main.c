/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:21:54 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/15 17:34:14 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_signal;

static int	control_and_c(int exit_status)
{
	if (g_signal == SIGINT)
		exit_status = EXIT_FAILURE;
	signal(SIGINT, SIG_IGN);
	return (exit_status);
}

void	minishell(t_shell *tshell)
{
	while (4)
	{
		set_signals(INTER);
		tshell->line = ft_readline();
		tshell->exit_state = control_and_c(tshell->exit_state);
		if (!tshell->line)
			exit_minishell(tshell);
		split_intotokens(tshell);
		split_intocomands(tshell, tshell->tokens);
		tshell->line = ft_free_str(tshell->line);
		split_intodoublelist(tshell);
		free_tokens(tshell);
		if (tshell->cmd_size && tshell->tree_cmd)
		{
			if (check_comand(tshell))
				redirect_and_execute(tshell);
		}
		free_comands(tshell);
		free_tree_cmds(tshell);
		rl_on_new_line();
	}
}

int	main(int argc, char **args, char **env)
{
	t_shell	*t_shell;
	int		exit_state;

	t_shell = NULL;
	if (argc != 1 || (ft_arr_strlen(args) > 2))
		print_err_args();
	t_shell = init_tshell(t_shell, env);
	if (!t_shell)
		return (1);
	minishell(t_shell);
	exit_state = t_shell->exit_state;
	t_shell = free_tshell(t_shell);
	exit(exit_state);
	return (0);
}
