/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:19:47 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/06 21:56:03 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_absolutepath(char *str)
{
	if (str[0] == '/')
		return (TRUE);
	return (FALSE);
}

/*
**	change env (oldpwd and pwd) depending on if it's absolute or relativ path
** Simply running cd without any arguments is equivalent 
** to cd ~ which goes to the $HOME directory.
*/
char	**change_my_env(t_cmd *cmd, char **env)
{
	char	*pwd;

	pwd = get_var_from_env("PWD", env);
	if (!pwd)
	{
		print_err_syntax("minishell: cd does not work if PWD is unset");
		return (env);
	}
	if (cmd->input == NULL)
	{
		env = change_pwd_home(env);
		env = change_oldpwd(pwd, env);
	}
	else if (is_absolutepath(cmd->input))
	{
		env = change_pwd_absolute(cmd->input, env);
		env = change_oldpwd(pwd, env);
	}
	else
		env = change_pwd_relative(cmd->input, env);
	return (env);
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
	        return (print_err_syntax("minishell: cd: HOME not set"));				
	}
	else if (chdir(cmd->input) == -1)
        return (print_err_syntax("minishell: unable to get path"));	
	return (1);
}

int	builtin_cd(t_cmd *cmd, char **env)
{
    if (change_dir(cmd, env))
    {
        env = change_my_env(cmd, env);
        return(0);
    }
    return (1);
}