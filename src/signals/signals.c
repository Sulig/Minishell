/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:12:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/25 16:59:04 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_get_pid()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(print_err_custom(MERR_FORK, 1));
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}

/*
 * If print is TRUE signals will be printed, otherwise they won't.
*/
void	signals_print_handler(int print)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (print == TRUE)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

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
