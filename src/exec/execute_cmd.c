/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:31:32 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/16 07:57:18 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Allocates and returns a string containing the full path of 'file' in 'dir'.
// Example: if 'dir' is /folder and 'file' is myfile, returns "/folder/myfile".
static char	*get_full_path(const char *dir, const char *file)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, file);
	free(tmp);
	return (full_path);
}

/*
** Searches de command in env PATH and returns the first full path
** if not founds exots with error
*/
char    *get_exec_path(const char *file, char **env)
{
    char    *path;
    char    **paths;
    int     i;

    paths = get_vars_from_env("PATH", env);
    i = -1;
    while (paths && paths[++i])
    {
        path = get_full_path(paths[i], file);
        if (path_exists(path) && !is_directory(path))
        {
            if (can_execute(path))
                return (path);
            else
            {
                free(path);
                print_err_syntax("permission denied");
                exit(126);
            }
        }
        free(path);
    }
    print_err_syntax("command not found");
    exit(127);
}

/*
** Execute not builtin commnand. first search path in env with this command
** if exists execute with execve
*/
void execute_cmd(t_cmd *cmd, char **env)
{
    char    *args;
    char    *path;

    path = cmd->comand;
    args = cmd ->options;
    if (!ft_strchr(path, '/'))
        path = get_exec_path(path, env);
    //else
    //    check_path(path);
}