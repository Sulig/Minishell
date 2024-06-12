/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 09:48:48 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:25:00 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(char **env)
{
	char	**tmp;

	while (*env)
	{
		if (ft_strchr(*env, '='))
		{
			tmp = get_key_value_pair(*env);
			if (tmp[1][0] != '\0')
				ft_putendl_fd(*env, STDOUT_FILENO);
			free_arr_2d(tmp);
		}
		env++;
	}
	return (0);
}
