/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:29:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/13 17:46:36 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* env_var_count:
*	Counts how many original environment variables there are.
*	Returns the number of environment variables.
*/
int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/* realloc_env_vars:
*	Reallocates memory for the global variable g_env_vars.
*
*	Returns a pointer to the new environment variables
*	or NULL in case of a memory allocation error.
*/
static char	**realloc_env_vars(t_shell *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

/* get_env_var_index:
*	Searches for the given variable in the environment variables.
*
*	Returns the index of the variable in the environment
*	matching the given string. Partial variable names are not
*	supported: the given string must be a full variable name.
*	Returns -1 if the string cannot be found in the environment.
*/
int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp_simple(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

/* set_env_var:
*	Adds an environment variable with the given key
*	corresponding to the given value. If the key already
*	exists in the environment variables, the value will
*	be overwritten. If not, it creates a new entry.
*
*	Returns 1 if the operation was successful, or 0 if
*	in case of error.
*/
int	set_env_var(t_shell *tshell, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(tshell->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (FALSE);
	if (idx != -1 && tshell->env[idx])
	{
		free_ptr(tshell->env[idx]);
		tshell->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(tshell->env);
		tshell->env = realloc_env_vars(tshell, idx + 1);
		if (!tshell->env)
			return (FALSE);
		tshell->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (TRUE);
}

/* remove_env_var:
*	Removes the variable at the given index from the
*	environment variables.
*
*	Returns 1 if the removal was successful, 0 if case
*	of an invalid index or a memory allocation error.
*/
int	remove_var_from_env(t_shell *tshell, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(tshell->env))
		return (FALSE);
	free_ptr(tshell->env[idx]);
	i = idx;
	count = idx;
	while (tshell->env[i + 1])
	{
		tshell->env[i] = ft_strdup(tshell->env[i + 1]);
		free_ptr(tshell->env[i + 1]);
		count++;
		i++;
	}
	tshell->env = realloc_env_vars(tshell, count);
	if (!tshell->env)
		return (FALSE);
	return (FALSE);
}
