/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 09:58:05 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/07 13:31:58 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	printvar_quoted(const char *var)
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

// Export every variable in 'args' to env. 
// If no errors are found, returns 0.
// Otherwise returns error with the proper message and exit_status.
int	builtin_export(t_cmd *cmd, char **env)
{
    int		exit_status;
    char	**args;
	char	*varname;
	int		i;

    exit_status = 0;
    if (cmd->input == NULL)
		return (export_noargs(env));
    args = ft_split(cmd->input, ' ');
	i = 0;
	while (args[i])
	{
		varname = env_get_varname(args[i]);
		if (varname == NULL)
			break;
		if (!env_valid_varname(varname))
		{
			free(varname);
			exit_status = print_err_syntax("export: invalid var name");			
			continue ;
		}	
		remove_env_var(args[i], env);
		env = append_arr_2d(env, varname);
		if (env == NULL)
			return (0);
		free(varname);
		i++;
	}
    free (args);
    return (exit_status);
}