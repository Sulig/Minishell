/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:12:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/30 17:31:14 by jguillot         ###   ########.fr       */
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


