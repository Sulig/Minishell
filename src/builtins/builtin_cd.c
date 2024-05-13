/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:19:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/13 17:38:43 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_relativepath(char *str)
{
	if (str[0] != '/')
		return (TRUE);
	return (FALSE);
}

// Makes sure the pointed 'path' string ends in '/'
static void	end_in_slash(char **path)
{
	if ((*path)[ft_strlen(*path)] != '/')
		ft_strjoin_free(path, "/");
}

/*
	if can't change directory (chdir return -1), exit statut = 1
	else change env (pwd, oldpwd), exit statut = 0
*/
int	change_dir(t_cmd *cmd, char **env)
{
	char	*home;

	home = get_var_from_env("HOME", env);
	if (cmd->input == NULL)
	{
		if (chdir(home) == -1)
			return (print_err_syntax ("minishell: cd: HOME not set"));
	}
	else if (chdir(cmd->input) == -1)
		return (print_err_syntax ("minishell: unable to get path"));
	return (1);
}

// Tries to change directory for any 'path' with 'str' at the end.
// If it succeeds, stops trying and retuns TRUE.
// FALSE otherwise.
static int	try_cdpath(char *str, char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = get_vars_from_env("CDPATH", env);
	if (path == NULL)
		return (FALSE);
	while (path[++i])
	{
		end_in_slash(&path[i]);
		ft_strjoin_free(&path[i], str);
		if (chdir(path[i]) == 0)
		{
			arrstr_free(path);
			return (TRUE);
		}
	}
	arrstr_free(path);
	return (FALSE);
}

// If the string 'str' uses the dir "." or ".." returns TRUE.
// Otherwise returns FALSE.
static int	is_same_or_parent_dir(char *str)
{
	if (str[0] != '.')
		return (FALSE);
	if (str[1] == '\0' || str[1] == '/')
		return (TRUE);
	if (str[1] == '.' && (str[2] == '\0' || str[2] == '/'))
		return (TRUE);
	return (FALSE);
}

// Changes the actual dir.
// If no 'args' is set, search for the env variable PATH.
// The first element of 'args' is taken as the new path.
// It it is a relative path tries appending CDPATH values, printing the current
// working dir on success.
// If some error is found returns after printing an error message.
int	builtin_cd(t_cmd *cmd, char **env)//char **args, char **env)
{
	char	*args;

	args = cmd->input;
	if (args == NULL)
	{
		if (chdir(get_var_from_env("HOME", env)) < 0)
			return (print_comun_error("error getting $HOME", 1));
		return (EXIT_SUCCESS);
	}
	if (args[0] == '\0')
		return (EXIT_SUCCESS);
	if (is_relativepath(args) && is_same_or_parent_dir(args) == FALSE)
	{
		if (try_cdpath(args, env))
			return (builtin_pwd());
	}
	if (chdir(args) < 0)
		return (print_comun_error("error setting cd", 1));
	return (EXIT_SUCCESS);
}
