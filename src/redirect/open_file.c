/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:45:58 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/10 18:45:50 by sadoming         ###   ########.fr       */
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
		print_err_custom("Can't open the file");
	return (fd_file);
}
