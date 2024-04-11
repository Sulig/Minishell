/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:07:51 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/11 18:31:13 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_simple_cmd(t_cmd *cmd, char **args)
{
    int exit_status;

	exit_status = 0;
    if (!cmd)
        return (1);
    if (is_builtin_name(cmd))
        exit_status = execute_builtin(cmd, exit_status, args);
    return (exit_status);
}
