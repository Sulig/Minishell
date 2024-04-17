/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:41:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:16 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	change path of pwd in env for relativ path
*/
char	**change_pwd_relative(char *path, char **env)
{
	char	**temp;
	char	**temp2;
	char	*pwd;
	int		i;

	i = 0;
	pwd = get_var_from_env("PWD", env);
	temp = ft_split(path, '/');
	temp2 = ft_split(pwd, '/');
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "..") == 0)
			temp2 = remove_last_elem_arr2d(temp2);
		else if (ft_strcmp(temp[i], ".") != 0)
			temp2 = append_arr_2d(temp2, temp[i]);
		i++;
	}
	env = change_pwd(temp2, env);
	env = change_oldpwd(pwd, env);
	free_arr_2d(temp);
	free_arr_2d(temp2);
	return (env);
}

/*
	change path of pwd in env for absolute path
*/
char	**change_pwd_absolute(char *path, char **env)
{
	int		i;
	int		pwd_index;
	char	**temp;
	char	*new_pwd;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (arr_2d_len(env) + 1));
	if (!temp)
		return (NULL);
	pwd_index = find_var_index_from_env("PWD", env);
	new_pwd = ft_strjoin_s("PWD=", path);
	while (env[i])
	{
		if (i == pwd_index)
			temp[i] = ft_strdup(new_pwd);
		else
			temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = NULL;
	free_arr_2d(env);
	free(new_pwd);
	return (temp);
}

/*
** change path of oldpwd in env
** return env with new oldpwd
*/
char	**change_oldpwd(char *pwd, char **env)
{
	char	*new_old_pwd;
	int		old_env_index;

	old_env_index = find_var_index_from_env("OLDPWD", env);
	new_old_pwd = ft_strjoin_s("OLDPWD=", pwd);
	free(env[old_env_index]);
	env[old_env_index] = ft_strdup(new_old_pwd);
	free(new_old_pwd);
	return (env);
}

/*
** change path of pwd in env to HOME
** return env with new oldpwd
*/
char	**change_pwd_home(char **env)
{
	char	*new_pwd;
	int		pwd_index;
	char	*home;

	home = get_var_from_env("HOME", env);
	pwd_index = find_var_index_from_env("PWD", env);
	new_pwd = ft_strjoin_s("PWD=", home);
	free(env[pwd_index]);
	env[pwd_index] = ft_strdup(new_pwd);
	free(new_pwd);
	free(home);
	return (env);
}

/*
	change path of pwd in env
	return env with new pwd
*/
char	**change_pwd(char **temp, char **env)
{
	int		pwd_place;
	char	*new_pwd;
	char	**aux;
	int		i;

	i = 0;
	pwd_place = find_var_index_from_env("PWD", env);
	aux = (char **)malloc(sizeof(char *) * (arr_2d_len(env) + 1));
	if (!aux)
		return (NULL);
	//pwd_place = find_var_line_from_env("PWD", env);
	new_pwd = concat_path(temp, "PWD=");
	while (env[i])
	{
		if (i == pwd_place)
			aux[i] = ft_strdup(new_pwd);
		else
			aux[i] = ft_strdup(env[i]);
		i++;
	}
	aux[i] = NULL;
	free_arr_2d(env);
	free(new_pwd);
	return (aux);
}
