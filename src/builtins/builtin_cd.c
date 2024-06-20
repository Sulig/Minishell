/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:19:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/20 18:22:34 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_relativepath(char *str)
{
	if (str[0] != '/')
		return (TRUE);
	return (FALSE);
}

static void	end_in_slash(char **path)
{
	if ((*path)[ft_strlen(*path)] != '/')
		ft_strjoin_free(path, "/");
}

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
		ft_strjoin_free_fst(path[i], str);
		if (chdir(path[i]) == 0)
		{
			arrstr_free(path);
			return (TRUE);
		}
	}
	arrstr_free(path);
	return (FALSE);
}

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

int	builtin_cd(t_cmd *cmd, t_shell *tshell)
{
	if (cmd->input == NULL)
	{
		if (chdir(get_var_from_env("HOME", tshell->env)) < 0)
			return (print_comun_error("minishell: cd: HOME not set", 1));
		change_pwds_home(tshell);
		return (EXIT_SUCCESS);
	}
	if (cmd->input[0] == '\0')
		return (EXIT_SUCCESS);
	if (is_relativepath(cmd->input)
		&& is_same_or_parent_dir(cmd->input) == FALSE)
	{
		if (try_cdpath(cmd->input, tshell->env))
		{
			change_oldpwd(tshell);
			if (!change_pwd(tshell))
				return (builtin_pwd());
			return (EXIT_FAILURE);
		}
	}
	if (chdir(cmd->input) < 0)
		return (print_comun_error("cd: no such file or directory", 1));
	change_pwds(tshell);
	return (EXIT_SUCCESS);
}
