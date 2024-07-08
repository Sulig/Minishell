/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:04:32 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/20 18:47:23 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	printvar_quoted(const char *var)
{
	while (*var != '=')
	{
		write(1, var, 1);
		++var;
	}
	write(1, "=\"", 2);
	++var;
	while (*var)
	{
		write(1, var, 1);
		++var;
	}
	write(1, "\"\n", 2);
}

static int	export_noargs(char **env)
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

int	process_args(char **args, int exit_status, t_shell *tshell)
{
	char	*varname;
	int		i;

	--args;
	while (++args && *args)
	{
		i = 0;
		varname = env_get_varname(*args);
		if (!env_valid_varname(varname))
		{
			exit_status = print_err_identifier("export", *args);
			free(varname);
			continue ;
		}
		while ((*args)[i] && (*args)[i] != '=')
			++i;
		if ((*args)[i++] == '=')
			set_env_var(varname, (*args) + i, tshell);
		else
			set_env_var(varname, NULL, tshell);
		if (varname)
			free(varname);
	}
	return (exit_status);
}

/*
* Export every variable in 'args' to env.
* If no errors are found, returns 0.
* Otherwise returns error with the proper message and exit_status.
*/
int	builtin_export(t_cmd *cmd, t_shell *tshell)
{
	int		exit_status;
	char	**args;
	char	**tmp;

	exit_status = 0;
	if (!cmd->input)
		return (export_noargs(tshell->env));
	//Maybe will be convenient to make a copy of input?
	args = ft_strarrdup(cmd->input);
	//Push the flags to **input?
	exit_status = process_args(args, exit_status, tshell);
	free_arr_2d(args);
	return (exit_status);
}
