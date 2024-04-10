/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_from_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:55:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/10 19:36:16 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Given that 'varname' points to the first character of a variable name,
// returns its value. If 'varname' does not exist, returns NULL.
char	*get_var_from_env(const char *varname, char **env)
{
	int		name_len;
	char	*var_line;

	var_line = find_var_line_from_env(varname, env);
	name_len = env_name_len(varname);
	if (var_line == NULL)
		return (NULL);
	return (var_line + name_len + 1);
}
