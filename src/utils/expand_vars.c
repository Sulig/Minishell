/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/04 19:58:57 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expansor_utils(char *str, char **env, int exit, int expand)
{
	char	*env_var;
	char	*tmp;
	char	*itoa;

	if (ft_strstr(str, "$?") && expand)
	{
		itoa = ft_itoa(exit);
		str = ft_free_str(str);
		return (itoa);
	}
	env_var = NULL;
	tmp = ft_strdup(str + 1);
	tmp = ft_strjoin_free_fst(tmp, "=");
	env_var = find_var_line_from_env(tmp, env);
	env_var = ft_strcut(env_var, '=', '>', 'y');
	tmp = ft_free_str(tmp);
	str = ft_free_str(str);
	return (ft_strdup(env_var));
}

/*
** Expansor
*	If encounters a $? && exp is 1 -> expand to tshell->exit_state
*	If te variable is inside of '' -> do not expand
*/
t_cmd	*expand_env_vars_cmd(t_shell *tshell, t_cmd *cmd, int exp)
{
	int		exit;

	exit = tshell->exit_state;
	/*
	if (cmd->name->toktype == ENV && cmd->name->location != IN_SINGLE_Q)
	{
		if (cmd->name->location == NO_QUOTED)
			cmd->name->content = expansor_utils(cmd->name->content, env, exit, exp)
	}
	*/
	// Manage array
	return (cmd);
}
