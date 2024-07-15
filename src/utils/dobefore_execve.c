/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dobefore_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/11 18:35:06 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	**join_and_separe(t_token **arr)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	t_token	**new_arr;

	i = 0;
	j = 0;
	new_arr = NULL;
	new_arr = push_intoarr(new_arr, arr[i]);
	if (!new_arr)
		return (NULL);
	while (arr[++i])
	{
		tmp = new_arr[j]->content;
		if (check_beforecreate(NULL, arr[i]))
			new_arr[j]->content = ft_strjoin_free_fst(tmp, arr[i]->content);
		else if (!check_beforecreate(NULL, arr[i]) && arr[i + 1])
		{
			new_arr = push_intoarr(new_arr, arr[++i]);
			j++;
		}
	}
	arr = clear_tarr(arr);
	return (new_arr);
}

/*
** Expand enviroment variables && Join args
*	In expansor, expands the enviroment variables
*		* If the variable is inside of '' -> do not expand
*		* If encounters a $?-> expand to tshell->exit_state
*		** The last rule is affected by LOCATION too
*	In Joining, joins the diferent args[]...
*		* If in intermediate position no contains a SPACE
*		** EX> [0]$?'$?'"$?" (BF Was agoruped into diferent positions)
*	And remove the input[x]->toktype == SPACE
*		* If this space is not quoted
*/
t_cmd	*dobefore_execve(t_shell *tshell, t_cmd *cmd)
{
	if (cmd->cmdtype != PIPE)
	{
		if (tshell)
			cmd = expand_env_vars_cmd(tshell, cmd, 1);
		if (cmd->input)
			cmd->input = join_and_separe(cmd->input);
	}
	return (cmd);
}
