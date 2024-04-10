/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-set_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:52:25 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/10 19:47:34 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_set_path(t_shell *tshell)
{
	char	*path;
	size_t	path_pos;

	path = tshell->env[ft_search_str(tshell->env, "PATH=")];
	if (path)
		path = ft_strcut(path, '=', '>', 'y');
	tshell->path = getcwd(tshell->path, 0);
	if (!my_strcmp(tshell->path, path))
	{
		path_pos = ft_search_str(tshell->env, "PATH");
		tshell->env[path_pos] = ft_free_str(tshell->env[path_pos]);
		path = ft_strdup("PATH=");
		path = ft_strjoin_free_fst(path, tshell->path);
		tshell->env[path_pos] = ft_strdup(path);
		path = ft_free_str(path);
	}
	if (!tshell->path)
		return (NULL);
	return (tshell->path);
}
