/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/28 19:08:16 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expansor_utils(char *str, char **env, int exit)
{
	char	*env_var;
	char	*tmp;

	if (my_strcmp("$?", str))
	{
		if (ft_strstr(str, "\1"))
		{
			str = ft_free_str(str);
			return (ft_itoa(exit));
		}
		return (str);
	}
	env_var = NULL;
	tmp = ft_strdup(str + 1);
	tmp = ft_strjoin_free_fst(tmp, "=");
	env_var = env[ft_search_str(env, tmp)];
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

/*
 * Expands the str.
 * 1. Create a list of tokens
 * 2. Expand each token
 * 3. Join again in str
*/
char	*expand_env_var_instr(char *str, char **env, int exit)
{
	t_list	*tokens;
	t_list	*first;
	t_token	*token;

	if (!ft_strstr(str, "$"))
		return (str);
	tokens = split_intotokens_forexpand(str);
	if (!tokens)
		return (str);
	first = tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ENV)
			token->content = expansor_utils(token->content, env, exit);
		tokens = tokens->next;
	}
	str = ft_free_str(str);
	str = join_again(first);
	tokens = free_tokens_list(&first);
	return (str);
}

static char	*expand_env_var_str(char *str, char **env, int exit)
{
	t_list	*tokens;
	t_list	*first;
	t_token	*token;

	if (!ft_strstr(str, "$"))
		return (str);
	tokens = split_intotokens_forexpand(str);
	fill_token_location(NULL, tokens);
	if (!tokens)
		return (str);
	first = tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ENV && token->location != IN_SINGLE_Q)
			token->content = expansor_utils(token->content, env, exit);
		tokens = tokens->next;
	}
	str = ft_free_str(str);
	str = join_again(first);
	tokens = free_tokens_list(&first);
	return (str);
}

t_cmd	*expand_env_vars_cmd(t_shell *tshell, t_cmd *cmd)
{
	int		exit;

	exit = tshell->exit_state;
	cmd->comand = expand_env_var_str(cmd->comand, tshell->env, exit);
	cmd->options = expand_env_var_str(cmd->options, tshell->env, exit);
	cmd->input = expand_env_var_str(cmd->input, tshell->env, exit);
	return (cmd);
}
