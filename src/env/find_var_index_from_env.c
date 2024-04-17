/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_index_from_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:34:19 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/17 16:56:56 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

/*
	Return the len of an str array (that is 0-terminated)
*/
int	strarr_len(char **array)
{
	int	cur;

	cur = 0;
	if (array)
		while (array[cur])
			cur++;
	return (cur);
}

int	find_var_index_from_env(char *elem, char **env)
{
	int	path_len;
	int	index;

	path_len = ft_strllen(elem);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(elem, env[index], path_len) == 0)
			break ;
		index++;
	}
	if (index == strarr_len(env))
		return (-1);
	return (index);
}
