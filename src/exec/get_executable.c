/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:23:50 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/21 19:15:55 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Allocates and returns a string containing the full path of 'file' in 'dir'.
// Example: if 'dir' is /folder and 'file' is myfile, returns "/folder/myfile".
static char	*get_full_path(const char *dir, const char *file)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, file);
	free(tmp);
	return (full_path);
}

// Searches for 'file' using the PATH env variable and returns the first
// full path for the executable file.
// If the file is not found or is not executable, prints an error and exits.
char	*get_executable(const char *file, char **env)
{
	char	*path;
	char	**paths;
	int		i;

	paths = get_vars_from_env("PATH", env);
	i = -1;
	while (paths && paths[++i])
	{
		path = get_full_path(paths[i], file);
		if (path_exists(path) && !is_directory(path))
		{
			if (can_execute(path))
				return (path);
			else
			{
				free(path);
				print_err_custom("permission denied", 126);
				exit(126);
			}
		}
		free(path);
	}
	print_comandnotfound((char *)file);
	exit(127);
}
