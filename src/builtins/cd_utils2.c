/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:25:51 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:50 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	return new pwd path
*/
char	*concat_path(char **env, char *str)
{
	char	*s;
	char	*temp;
	int		i;

	i = 0;
	s = ft_strdup(str);
	temp = ft_strdup(s);
	free(s);
	while (env[i])
	{
		s = ft_strjoin_s(temp, "/");
		free(temp);
		temp = ft_strdup(s);
		free(s);
		s = ft_strjoin_s(temp, env[i]);
		free(temp);
		temp = ft_strdup(s);
		free(s);
		i++;
	}
	s = ft_strdup(temp);
	free(temp);
	return (s);
}

int	check_cd_input (t_cmd *cmd, t_shell *tshell)
{
	if (chdir(get_var_from_env("HOME", tshell->env)) < 0)
			return (print_comun_error("minishell: cd: HOME not set", 1));
		change_pwds_home(tshell);
		return (EXIT_SUCCESS);
	if (cmd->input[0]->content == NULL)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
