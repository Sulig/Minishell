/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars_from_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:34:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:26:37 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Allocates and returns a NULL-terminated array of strings containing the
* values of the colon-separated environment value 'varname'.
* If 'varname' does not exist, returns NULL.
*/
char	**get_vars_from_env(const char *varname, char **env)
{
	char	*value;
	char	**values;

	value = get_var_from_env(varname, env);
	if (!value)
		return (NULL);
	values = ft_split(value, ':');
	return (values);
}
