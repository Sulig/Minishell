/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:27:45 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	link_heredoc(int n)
{
	char	*filename;
	int		fd_file;
	int		err;

	filename = heredoc_filename(n);
	fd_file = open_file(filename, O_RDONLY);
	free(filename);
	if (fd_file == -1)
		return (EXIT_FAILURE);
	err = dup2(fd_file, STDIN_FILENO);
	if (!err)
		err = close(fd_file);
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
