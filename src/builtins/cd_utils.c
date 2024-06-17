/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:41:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/13 17:10:30 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_oldpwd(t_shell *tshell)
{
	char	*pwd;
	char	*oldpwd;
	int		oldpwd_index;

	pwd = get_var_from_env("PWD", tshell->env);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	oldpwd_index = find_var_index_from_env("OLDPWD", tshell->env);
	free(tshell->env[oldpwd_index]);
	tshell->env[oldpwd_index] = ft_strdup(oldpwd);
	free(oldpwd);
}

void	change_pwd_to_home(t_shell *tshell)
{
	char	*home;
	char	*pwd;
	int		pwd_index;

	home = get_var_from_env("HOME", tshell->env);
	pwd_index = find_var_index_from_env("PWD", tshell->env);
	pwd = ft_strjoin("PWD=", home);
	free(tshell->env[pwd_index]);
	tshell->env[pwd_index] = ft_strdup(pwd);
	free(pwd);
}

int	change_pwd(t_shell *tshell)
{
	char	*buffer;
	int		pwd_index;
	char	*pwd;

	buffer = NULL;
	buffer = getcwd(buffer, 1024);
	if (!buffer)
		return (EXIT_FAILURE);
	pwd_index = find_var_index_from_env("PWD", tshell->env);
	pwd = ft_strjoin("PWD=", buffer);
	free(tshell->env[pwd_index]);
	tshell->env[pwd_index] = ft_strdup(pwd);
	free(pwd);
	free(buffer);
	return (EXIT_SUCCESS);
}

void	change_pwds(t_shell *tshell)
{
	change_oldpwd(tshell);
	change_pwd_to_home(tshell);
}
