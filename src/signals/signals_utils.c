/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:37:52 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/30 17:30:58 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Stops listening to SIGINT and SIGQUIT signals.
void	stop_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	inter_handler(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	heredoc_handler(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Sets the signal mode.
 * If mode == 1 -> INTER mode
 * If mode == -1 -> NOT INTER mode
 * If mode == 0 -> HEREDOC
*/
void	set_signals(int mode)
{
	if (mode == INTER)
	{
		g_signal = 0;
		signal(SIGINT, inter_handler);
		signal(SIGQUIT, SIG_IGN);
		signals_print_handler(FALSE);
	}
	if (mode == HERE)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == NON_INTER)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signals_print_handler(TRUE);
	}
}
