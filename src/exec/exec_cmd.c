/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:11:04 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/11 17:54:58 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// If the given 'path' is not executable, prints an error message and exits.
static void	check_path(const char *path)
{
	if (!path_exists(path))
		exit(print_comun_error("No such file or directory", 127));
	if (is_directory(path))
		exit(print_comun_error("is a directory", 126));
	if (!can_execute(path))
		exit(print_comun_error("Permission denied", 126));
}

char	**parse_args(char *path, char *args)
{
	char	*arg[3];

	arg[0] = path;
	arg[1] = args;
	arg[2] = NULL;
	return (ft_strarrdup(arg));
}

char	**parse_expr(char *path, char *args)
{
	char	**splited;
	char	**arg;
	int		items;
	int		i;

	splited = ft_split(args, ' ');
	items = ft_arr_strlen(splited);
	arg = malloc(sizeof(char *) * (items + 2));
	i = 1;
	arg[0] = path;
	while (i <= items)
	{
		arg[i] = ft_strdup(splited[i - 1]);
		i++;
	}
	arg[i] = NULL;
	free_arr_2d(splited);
	return (ft_strarrdup(arg));
}

// Executes the shell command 'cmd' and exits, assuming 'cmd' is a non-empty
// NULL-terminated array of strings in which the first element is the path or
// name of the program and the following (if any) are the arguments.
// On error, prints an error message and exits with the appropriate exit code.
void	exec_cmd(t_cmd *cmd, char **env)
{
	char	**args;
	char	*path;

	path = cmd->comand;
	if (!ft_strchr(path, '/'))
		path = get_executable(path, env);
	else
		check_path(path);
	if (!ft_strstr(path, "expr") && cmd->options != NULL)
		args = parse_args(path, cmd->options);
	else
		args = parse_expr(path, cmd->input);
	execve(path, args, env);
	print_comandnotfound(cmd->comand);
	exit(EXIT_FAILURE);
}
