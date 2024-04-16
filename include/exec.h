/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:09:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/15 18:52:31 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int     execute_simple_cmd(t_cmd *cmd, char **env);
int     execute_builtin(t_cmd *cmd, int exit_status, char **env, int is_child);
void    execute_cmd(t_cmd *cmd, char **env);
int     path_exists(const char *path);
int     is_directory(const char *path);
int     can_execute(const char *path);

# endif