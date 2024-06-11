/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:09:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/11 18:45:38 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		execute_builtin(t_list *cmd, t_shell *tshell, int is_child);
int		path_exists(const char *path);
int		is_directory(const char *path);
int		can_execute(const char *path);
void	execute_command(t_list *cmds, t_shell *tshell);
void	exec_cmd(t_cmd *cmd, char **env);
char	*get_executable(const char *file, char **env);
t_cmd	*expand_exit_status(t_shell *tshell, t_cmd *cmd);

#endif
