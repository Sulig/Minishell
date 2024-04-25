/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_write_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:20:06 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 16:20:27 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Links the standard output to the write end of a pipe, closing the read end.
void	link_write_end(int *fd_pipe)
{
	close(fd_pipe[READ_END]);
	dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
	close(fd_pipe[WRITE_END]);
}
