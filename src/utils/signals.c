/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:12:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/15 15:40:05 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../../include/minishell.h"

void	ft_newline_redisplay(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf_fd(1, "\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
 * Capt signals
 * If mode == 0 -> Normal mode
 * If mode == 1 -> Heredoc mode
*/
void	start_signals(void)
{
	//struct sigaction	s_sig;

	//s_sig.flags = SA_SIGINFO;
	//s_sig.sa_sigaction = kill;
	signal(SIGQUIT, SIG_IGN);
	//if (mode == 0)
		signal(SIGINT, ft_newline_redisplay);
	//CONTROL + C IN HEREDOC
}
