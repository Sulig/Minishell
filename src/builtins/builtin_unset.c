/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:37:01 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/11 17:56:50 by sadoming         ###   ########.fr       */
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
		i = 0;
        args = ft_split(cmd->input, ' ');
		if (!ft_arr_strlen(args))
			return (0);
        while (args[i])
        {
            if (env_valid_varname(args[i]))
			    remove_env_var(args[i], env);
            else
			    exit_status = print_err_custom("unset: error getting env var");
            i++;
        }
    }
	return (exit_status);
}
