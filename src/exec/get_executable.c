/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:23:50 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/14 19:15:00 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_full_path(const char *dir, const char *file)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin_s(dir, "/");
	full_path = ft_strjoin_s(tmp, file);
	free(tmp);
	return (full_path);
}

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
