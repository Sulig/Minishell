/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/11 17:56:41 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expansor_utils(char *str, char **env, int exit, int expand)
{
	char	*env_var;
	char	*tmp;
	char	*itoa;

	if (ft_strstr(str, "$?") && expand == 1)
	{
		itoa = ft_itoa(exit);
		tmp = ft_strinter(str, itoa, ft_cnt_tostr(str, "$?") + 2);
		str = ft_free_str(str);
		itoa = ft_free_str(itoa);
		tmp = ft_strremove(tmp, "$?");
		return (tmp);
	}
	else if (ft_strstr(str, "$?") && (!expand || expand == 2))
		return (str);
	env_var = NULL;
	tmp = ft_strdup(str + ft_cnttoch_in(str, '$'));
	tmp = ft_strjoin_free_fst(tmp, "=");
	env_var = find_var_line_from_env(tmp, env);
	env_var = ft_strcut(env_var, '=', '>', 'y');
	tmp = ft_free_str(tmp);
	str = ft_free_str(str);
	return (ft_strdup(env_var));
}

static char	*join_again(t_list *tokens)
{
	t_token	*token;
	char	*joined;

	joined = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		joined = ft_strjoin_free_fst(joined, token->content);
		tokens = tokens->next;
	}
	return (joined);
}

static char	*expand_str(char *str, char **env, int exit, int exp)
{
	t_list	*tokens;
	t_list	*first;
	t_token	*token;

	if (!ft_strstr(str, "$"))
		return (str);
	tokens = splitline_intotokens(str);
	if (!tokens)
		return (str);
	tokens = fill_token_location(tokens);
	first = tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ENV && token->location != IN_SINGLE_Q)
			token->content = expansor_utils(token->content, env, exit, exp);
		tokens = tokens->next;
	}
	str = ft_free_str(str);
	str = join_again(first);
	tokens = free_tokens_list(&first);
	return (str);
}

static t_token	**expand_intoarr(t_token **arr, char **env, int exit, int exp)
{
	size_t	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i]->toktype == ENV && arr[i]->location != IN_SINGLE_Q)
			arr[i]->content = expand_str(arr[i]->content, env, exit, exp);
		if (ft_strstr(arr[i]->content, "$"))
			arr[i]->toktype = ENV;
		if (!ft_strllen(arr[i]->content))
		{
			arr = pop_outarr(arr, i);
			i = -1;
		}
		if (!len_of_tokens(arr))
			return (clear_tarr(arr));
	}
	return (arr);
}

/*
** Expansor
*	If encounters a $? && exp is 1 -> expand to tshell->exit_state
*	If te variable is inside of '' -> do not expand
*/
t_cmd	*expand_env_vars_cmd(t_shell *tshell, t_cmd *cmd, int exp)
{
	int		exit;
	char	*tmp;

	exit = tshell->exit_state;
	if (cmd->name->toktype == ENV && cmd->name->location != IN_SINGLE_Q)
	{
		tmp = cmd->name->content;
		cmd->name->content = expand_str(tmp, tshell->env, exit, 1);
		if (!ft_strstr(cmd->name->content, "$"))
			cmd->name->toktype = ARGS;
		else
			cmd->name->toktype = ENV;
	}
	if (cmd->flags && exp)
		cmd->flags = expand_intoarr(cmd->flags, tshell->env, exit, exp);
	if (cmd->input && exp)
		cmd->input = expand_intoarr(cmd->input, tshell->env, exit, exp);
	return (cmd);
}
