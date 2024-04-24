/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:11:04 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 17:54:13 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// If the given 'path' is not executable, prints an error message and exits.
static void	check_path(const char *path)
{
	if (!path_exists(path))
		exit(print_err_custom("No such file or directory", 127));
	if (is_directory(path))
		exit(print_err_custom("is a directory", 126));
	if (!can_execute(path))
		exit(print_err_custom("Permission denied", 126));
}

char **parse_args(char *path, char *args)
{
    char **arg;
    char *aux;

    aux = ft_strdup(path);
    if (args)
    {
        aux = ft_strjoin_free_fst(aux,"|");
        aux = ft_strjoin_free_fst(aux, args);
    }
    arg = ft_split(aux,'|');
    return (arg);
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
    args = parse_args(path, cmd->options);

	if (!ft_strchr(path, '/'))
		path = get_executable(path, env);
	else
		check_path(path);
	execve(path, args, env);
	print_err_custom("command not found", 127);
	exit(EXIT_FAILURE);
}
