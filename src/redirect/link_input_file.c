/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_input_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:52:02 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/11 12:52:21 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Opens the file 'filename' and links it to the standard input.
// Returns the appropriate exit code after printing any error message.
int	link_input_file(const char *filename)
{
	int	fd_file;
	int	ret;

	fd_file = open_file(filename, O_RDONLY);
	if (fd_file == -1)
		return (EXIT_FAILURE);
	ret = dup2(fd_file, STDIN_FILENO);
	if (ret == -1)
		return (EXIT_FAILURE);
	ret = close(fd_file);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
