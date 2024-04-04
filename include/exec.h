/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:09:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 18:02:59 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int execute_simple_cmd(t_cmd *cmd, char **env);
int execute_builtin(t_cmd *cmd, int exit_status, char **env, int is_child);

# endif