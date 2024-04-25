/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:09:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 12:11:35 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		execute_builtin(t_list *cmd, int exit_status, char **env, int is_child);
int		path_exists(const char *path);
int		is_directory(const char *path);
int		can_execute(const char *path);
void	execute_command(t_list *cmds, int exit_status, char **env);
void	exec_cmd(t_cmd *cmd, char **env);
char	*get_executable(const char *file, char **env);

#endif
