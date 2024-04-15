/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-set_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:52:25 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/15 20:09:45 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_set_path(t_shell *tshell)
{
	size_t	path_pos;
	char	*path;

	path_pos = ft_search_str(tshell->env, "PATH=");
	print_all_arrstr(tshell->env);
	ft_printf(B);
	ft_printf("\nPos of encountered: %u\n", path_pos);
	path = ft_strdup(tshell->env[path_pos]);
	if (!path)

	if (ft_strllen(path))
	{
		tshell->path = ft_strcut(tshell->path, '=', '>', 'y');
	}
	ft_printf("Content: %s\n\n", tshell->path);
}
