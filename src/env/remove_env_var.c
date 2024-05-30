/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:01:46 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 19:10:23 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Removes the environment variable 'varname'.
void	remove_env_var(char *varname, t_shell *tshell)
{
	int		var_index;

	var_index = find_var_index_from_env(varname, tshell->env);
	if (var_index >= 0)
		tshell->env = remove_elem_arr2d(tshell->env, var_index);
}
