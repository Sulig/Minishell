/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:38:41 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:22:14 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/* Historical signals specified by POSIX. */
# define SIGHUP		1
# define SIGQUIT	3
# define SIGTRAP	5
# define SIGKILL	9
# define SIGPIPE	13
# define SIGALRM	14

/* ISO C99 signals.  */
# define SIGINT		2
# define SIGILL		4
# define SIGABRT	6
# define SIGFPE		8
# define SIGSEGV	11
# define SIGTERM	15

/* MODES OF SETTING SIGNALS */
# define INTER 1
# define NON_INTER -1
# define HERE 0

extern int		g_signal;

void	set_signals(int mode);
void	start_signals(void);
void	stop_signals(void);
void	signals_print_handler(int print);

#endif
