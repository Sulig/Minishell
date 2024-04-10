/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:37:01 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/07 12:38:32 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	builtin_unset(t_cmd *cmd, char **env)
{
	int     i;
	int     exit_status;
    char    **args;

	exit_status = 0;
    if (cmd->input != NULL)
    {
        args = ft_split(cmd->input, ' ');
        while (args)
        {
            if (env_valid_varname(*args))
			    remove_env_var(args[i], env);
            else
			    exit_status = print_err_syntax("unset: error getting env var");
            args++;
        }
    }
	return (exit_status);
}