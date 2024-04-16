/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:01:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 17:15:43 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_path(t_shell *tshell)
{
	char	*path;

	tshell->path = NULL;
	path = tshell->env[ft_search_str(tshell->env, "PATH=")];
	if (path)
	{
		path = ft_strcut(path, '=', '>', 'y');
		tshell->path = ft_split(path, ':');
	}
	else
		print_err_custom(MERR_NOPATH, 1);
}
