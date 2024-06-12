/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_line_from_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:22:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:26:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_var_line_from_env(const char *varname, char **env)
{
	int	name_len;

	name_len = env_name_len(varname);
	if (name_len == 0)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, varname, name_len)
			&& (*env)[name_len] && (*env)[name_len] == '=')
			return ((char *)*env);
		++env;
	}
	return (NULL);
}
