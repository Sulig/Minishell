/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_read_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:17:23 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:14:35 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Links the standard output to the read end of a pipe, closing the write end.
void	link_read_end(int *fd_pipe)
{
	close(fd_pipe[WRITE_END]);
	dup2(fd_pipe[READ_END], STDIN_FILENO);
	close(fd_pipe[READ_END]);
}
