/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_read_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:17:23 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:28:08 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	link_read_end(int *fd_pipe)
{
	close(fd_pipe[WRITE_END]);
	dup2(fd_pipe[READ_END], STDIN_FILENO);
	close(fd_pipe[READ_END]);
}
