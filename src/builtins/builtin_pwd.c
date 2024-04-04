/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:45:42 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 18:54:19 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* pwd with no options
 * - print the full filename of the current working directory
 */

/* external function that we may use :
 * - char *getcwd(char *buf, size_t size) : this function return a 
 * null-terminated string containing an absolute pathname that is the current
 * working directory of the calling process. The pathname is returned
 * as the function result and via the argument 'buf', which is of length 'size'.
 * If the length of the absolute pathname of the current working directory,
 * including the terminating null byte, exceeds 'size' bytes, NULL is returned,
 * and 'errno' is set the ERANGE; an application should check for this error,
 * and allocate a larger buffer if necessary.
 * The function allocates the buffer dynamically using 'malloc' if 'buf' is NULL.
 * In this case, the allocated buffer hat the length 'size' unless 'size'
 * is zero, when 'buf' is allocated as big as necessary. The caller should
 * 'free' the returned buffer.
 */

int	builtin_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 42);
	if (!buffer)
	{
		print_err_syntax("error getting pwd");
		return (2);
	}
	write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
