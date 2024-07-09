/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:11:04 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/25 15:49:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_path(const char *path)
{
	if (!path_exists(path))
		exit(print_comun_error("No such file or directory", 127));
	if (is_directory(path))
		exit(print_comun_error("is a directory", 126));
	if (!can_execute(path))
		exit(print_comun_error("Permission denied", 126));
}

/*
* Executes the shell command 'cmd' and exits, assuming 'cmd' is a non-empty
* NULL-terminated array of strings in which the first element is the path or
* name of the program and the following (if any) are the arguments.
* On error, prints an error message and exits with the appropriate exit code.
*/
void	exec_cmd(t_cmd *cmd, char **env)
{
	char	**flags;
	char	**input;
	char	*path;
	char	**args;

	path = cmd->name->content;
	if (!ft_strchr(path, '/'))
		path = get_executable(path, env);
	else
		check_path(path);
	flags = get_arr_flags_from_cmd(cmd);
	input = get_arr_input_from_cmd(cmd);

	args = joinpath_withargs(path, flags, input);
	flags = ft_auto_free_arr(flags);
	input = ft_auto_free_arr(input);
	execve(path, args, env);
	print_comandnotfound(cmd->name->content);
	exit(EXIT_FAILURE);
}
