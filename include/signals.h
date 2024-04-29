/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:38:41 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 16:24:07 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/* Historical signals specified by POSIX. */
# define SIGHUP		1	/* Hangup.  */
# define SIGQUIT		3	/* Quit.  */
# define SIGTRAP		5	/* Trace/breakpoint trap.  */
# define SIGKILL		9	/* Killed.  */
# define SIGPIPE		13	/* Broken pipe.  */
# define SIGALRM		14	/* Alarm clock.  */

/* ISO C99 signals.  */
# define SIGINT		2	/* Interactive attention signal.  */
# define SIGILL		4	/* Illegal instruction.  */
# define SIGABRT		6	/* Abnormal termination.  */
# define SIGFPE		8	/* Erroneous arithmetic operation.  */
# define SIGSEGV		11	/* Invalid access to storage.  */
# define SIGTERM		15	/* Termination request.  */

// MODES OF SETTING SIGNALS

# define INTER 1
# define NON_INTER -1

void	start_signals(void);
void	stop_signals(void);
void	signals_print_handler(int print);

#endif
