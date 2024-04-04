/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:07:51 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 18:21:16 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_simple_cmd(t_cmd *cmd, char **args)
{
    int exit_status;

    if (!cmd)
        return (1);
    if (is_builtin_name(cmd->comand))
        exit_status = execute_builtin(cmd, exit_status, args, FALSE);
    return (exit_status);
}