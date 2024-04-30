/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:45:58 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/30 18:00:13 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Opens the file 'filename' with the 'flags' and returns its file descriptor.
 * On failure, prints an error message and returns -1 (setting errno).
*/
int	open_file(const char *filename, int flags)
{
	int	fd_file;

	fd_file = open(filename, flags, OPEN_FILE_MODE);
	if (fd_file == -1)
		print_comun_error(MERR_FILE, 127);
	return (fd_file);
}
