/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:01:46 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:07:09 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Removes the environment variable 'varname'.
void	remove_env_var(char *varname, char **env)
{
	int		var_index;

	var_index = find_var_index_from_env(varname, env);
	if (var_index >= 0)
		env = remove_elem_arr2d(env, var_index);
}
