/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:44:53 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:09:46 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Returns TRUE if 'path' is an executable file. Otherwise, returns FALSE.
*/
int	can_execute(const char *path)
{
	if (access(path, X_OK) == -1)
		return (FALSE);
	return (TRUE);
}

/*
 * Returns TRUE if the given 'path' is a directory. Otherwise, returns FALSE.
*/
int	is_directory(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (TRUE);
	return (FALSE);
}

/*
 * Returns TRUE if the given 'path' exists. Otherwise, returns FALSE.
*/
int	path_exists(const char *path)
{
	if (access(path, F_OK) == -1)
		return (FALSE);
	return (TRUE);
}
