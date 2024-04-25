/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 09:58:05 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:00:08 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	printvar_quoted(const char *var)
{
	while (*var != '=')
	{
		write (1, var, 1);
		++var;
	}
	write (1, "=\"", 2);
	++var;
	while (*var)
	{
		write (1, var, 1);
		++var;
	}
	write (1, "\"\n", 2);
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
			printvar_quoted(env[i]);
		}
	}
	return (0);
}

int	args_export(char **args, char **env)
{
	int		exit_status;
	char	*varname;
	int		i;

	exit_status = 0;
	if (!*args)
		return (export_noargs(env));
	--args;
	while (++args && *args)
	{
		i = 0;
		varname = env_get_varname(*args);
		if (!env_valid_varname(varname))
		{
			exit_status = print_err_custom("not a valid identifier", 1);
			free(varname);
			continue ;
		}
		while ((*args)[i] && (*args)[i] != '=')
			++i;
		if ((*args)[i++] == '=')
			env_set_var(varname, (*args) + i, env);
		free(varname);
	}
	return (exit_status);
}

// Export every variable in 'args' to env.
// If no errors are found, returns 0.
// Otherwise returns error with the proper message and exit_status.
int	builtin_export(t_cmd *cmd, char **env)
{
	char	**args;

	args = ft_split(cmd->input, ' ');
	return (args_export(args, env));
}
