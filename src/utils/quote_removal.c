/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/11 17:00:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	**unquote_intoarr(t_token **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i]->toktype == D_QUOTE)
			arr[i]->location = IN_DOUBLE_Q;
		else if (arr[i]->toktype == S_QUOTE)
			arr[i]->location = IN_SINGLE_Q;
		if (arr[i]->location == IN_DOUBLE_Q)
			arr[i]->content = ft_strremove(arr[i]->content, "\"");
		else if (arr[i]->location == IN_SINGLE_Q)
			arr[i]->content = ft_strremove(arr[i]->content, "\'");
		if (ft_strstr(arr[i]->content, "$") && ft_strllen(arr[i]->content) >= 2)
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
	char	*tmp;

	tmp = cmd->name->content;
	if (cmd->cmdtype == CMD)
		cmd->name->toktype = ARGS;
	if (ft_cnt_tostr(tmp, "\"") < ft_cnt_tostr(tmp, "\'"))
		cmd->name->location = IN_DOUBLE_Q;
	else if (ft_cnt_tostr(tmp, "\'") < ft_cnt_tostr(tmp, "\""))
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

/*
** Remplace cmd name for 1st input content
*/
t_cmd	*remplace_cmdname(t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	cmd->name->content = ft_free_str(cmd->name->content);
	free(cmd->name);
	cmd->name = duplicate_token(cmd->input[0]);
	cmd->input = pop_outarr(cmd->input, 0);
	if (len_of_tokens(cmd->input))
		cmd->input = clean_array(cmd->input);
	else
		cmd->input = clear_tarr(cmd->input);
	tmp = ft_strtrim(cmd->name->content, " ");
	cmd->name->content = ft_strremplace(cmd->name->content, tmp);
	tmp = ft_free_str(tmp);
	return (cmd);
}
