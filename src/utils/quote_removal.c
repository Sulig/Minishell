/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/04 19:40:11 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	**unquote_intoarr(t_token **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strstr(arr[i]->content, "\""))
			arr[i]->location = IN_DOUBLE_Q;
		else if (ft_strstr(arr[i]->content, "\'"))
			arr[i]->location = IN_SINGLE_Q;
		if (arr[i]->location == IN_SINGLE_Q)
			arr[i]->content = ft_strremove(arr[i]->content, "\'");
		else if (arr[i]->location == IN_DOUBLE_Q)
			arr[i]->content = ft_strremove(arr[i]->content, "\"");
		if (ft_strstr(arr[i]->content, "$") && ft_strllen(arr[i]->content) > 2)
			if (arr[i]->location != IN_SINGLE_Q)
				arr[i]->toktype = ENV;
	}
	return (arr);
}

/*
** Unquoting
*	The unquoter will asing the location with the quote encountered.
*	NO_QUOTED || IN_SINGLE_Q '' || IN_DOUBLE_Q ""
*	By deffault, if no quote encountered the location is NO_QUOTED
*	If encounters a env_var && can expand
*		** The toktype will be ENV
*/
t_cmd	*quote_removal(t_cmd *cmd)
{
	if (cmd->cmdtype == CMD)
		cmd->name->toktype = ARGS;
	if (ft_strstr(cmd->name->content, "\""))
		cmd->name->location = IN_DOUBLE_Q;
	else if (ft_strstr(cmd->name->content, "\'"))
		cmd->name->location = IN_SINGLE_Q;
	if (cmd->name->location == IN_SINGLE_Q)
		cmd->name->content = ft_strremove(cmd->name->content, "\'");
	else if (cmd->name->location == IN_DOUBLE_Q)
		cmd->name->content = ft_strremove(cmd->name->content, "\"");
	if (ft_strstr(cmd->name->content, "$"))
		if (ft_strllen(cmd->name->content) > 2)
			if (cmd->name->location != IN_SINGLE_Q)
				cmd->name->toktype = ENV;
	if (cmd->flags)
		cmd->flags = unquote_intoarr(cmd->flags);
	if (cmd->input)
		cmd->input = unquote_intoarr(cmd->input);
	return (cmd);
}
