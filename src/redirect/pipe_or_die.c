/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_or_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:37 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:28:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_or_die(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
	{
		print_err_custom("pipe error", 1);
		exit (1);
	}
}
