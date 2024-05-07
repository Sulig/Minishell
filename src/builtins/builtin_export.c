/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:04:32 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/07 20:39:27 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* get_key_value_pair:
*	Separates the given argument into a key-value pair
*	for the environment variable.
*	Returns an array of 2 strings containing the key and the
*	value of the new environment variable.
*	Returns NULL in case of error.
*/
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

/*
** If no args
** Prints the variables in env starting with
** declare -x and returns 0.
*/
int	export_noargs(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			//printvar_quoted(env[i]);
		}
	}
	return (EXIT_SUCCESS);
}

/* is_valid_env_var_key:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.
*/
int	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (FALSE);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	args_export(char **args, t_shell *tshell)
{
	int		i;
	char	**tmp;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	i = 0;
	if (!args[i])
		return (export_noargs(tshell->env));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{

			exit_status = print_comun_error("not a valid identifier", 1);
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(tshell, tmp[0], tmp[1]);
			free_arr_2d(tmp);
		}
		i++;
	}
	return (exit_status);
}
// Export every variable in 'args' to env.
// If no errors are found, returns 0.
// Otherwise returns error with the proper message and exit_status.
int	builtin_export(t_cmd *cmd, t_shell *tshell)
{
	char **args;

	if (cmd->input == NULL)
		return (export_noargs(tshell->env));
	args = ft_split(cmd->input, ' ');
	return (args_export(args, tshell));
}
