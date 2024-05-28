/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:29:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/28 18:19:38 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Allocates and returns a string consisting of 'varname' + "=" + 'value'.
static char	*join_varline(const char *varname, const char *value)
{
	char	*varline;
	size_t	varline_len;
	int		i;

	varline_len = ft_strlen(varname) + ft_strlen(value) + 1;
	varline = (char *)p_malloc(sizeof(char) * (varline_len + 1));
	i = 0;
	while (*varname)
		varline[i++] = *varname++;
	varline[i++] = '=';
	while (*value)
		varline[i++] = *value++;
	varline[i] = '\0';
	return (varline);
}

// Sets the environment variable 'varname' to 'value', creating it if needed.
void	set_env_var(const char *varname, const char *value, t_shell *tshell)
{
	int		var_index;
	char	*varline;

	if (value != NULL)
		varline = join_varline(varname, value);
	else
		varline = join_varline(varname, "");
	var_index = find_var_index_from_env((char *)varname, (char **)tshell->env);
	if (var_index == -1)
		tshell->env = arrstr_add(tshell->env, varline);
	else
		tshell->env = arrstr_set(tshell->env, varline, var_index);
	free(varline);
}

