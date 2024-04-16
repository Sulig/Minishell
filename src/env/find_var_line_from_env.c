/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_line_from_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:22:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/16 07:38:50 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Returns a pointer to the first character of the line containing the
// environment variable 'varname'. If 'varname' is not found returns NULL.
char	*find_var_line_from_env(const char *varname, char **env)
{
	int	name_len;

	name_len = env_name_len(varname);
	if (name_len == 0)
		return (NULL);
	while (*env)
	{
		//printf("ENV-> %s\n",env);
		if (!ft_strncmp(*env, varname, name_len)
			&& (*env)[name_len] && (*env)[name_len] == '=')
			return ((char *)*env);
		++env;
	}
	return (NULL);
}