/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:53:50 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/01 20:54:11 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Links the 'n'-th command's here document to the standard input.
// Returns the appropriate exit code after printing any error message.
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
