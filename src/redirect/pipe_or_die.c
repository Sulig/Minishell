/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_or_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:37 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 16:08:04 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Creates a pipe and allocates a pair of file descriptors at 'fd_pipe'.
// On failure, prints an error message and exits.
void	pipe_or_die(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
	{
		print_err_custom("pipe error", 1);
		exit (1);
	}
}
