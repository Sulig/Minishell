/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 09:48:48 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:02:44 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Lists the enviroment variables with its values. Returns 0
int	builtin_env(char **env)
{
	while (*env)
	{
		if (ft_strchr(*env, '='))
			ft_putendl_fd(*env, STDOUT_FILENO);
		env++;
	}
	return (0);
}
