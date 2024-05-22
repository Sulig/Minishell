/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 09:48:48 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/22 18:53:43 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Lists the enviroment variables with its values. Returns 0
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
