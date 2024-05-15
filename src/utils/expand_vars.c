/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/15 16:54:23 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expansor_utils(char *str, char **env, int exit)
{
	char	*env_var;
	char	*tmp;

	if (my_strcmp("$?", str))
	{
		if (ft_strstr(str, "\1") || ft_strstr(str, "\2"))
		{
			if (ft_strstr(str, "\1"))
			{
				str = ft_free_str(str);
				return (ft_itoa(exit));
			}
			str = ft_strremove(str, "\2");
		}
		str = ft_free_str(str);
		return (ft_itoa(exit));
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

static enum e_toktype	env_var_newtoktype(t_token *token)
{
	if (my_strcmp("$?", token->content))
		return (ARGS);
	if (ft_strchr(token->content, '$'))
		if (token->location != IN_SINGLE_Q)
			return (ENV);
	return (ARGS);
}

void	expand_env_var(t_shell *tshell)
{
	t_list	*tokens;
	t_token	*token;
	char	*env_var;

	tokens = tshell->tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ENV && token->location != IN_SINGLE_Q)
		{
			token->content = ft_strjoin_free_fst(token->content, "=");
			env_var = token->content + 1;
			env_var = tshell->env[ft_search_str(tshell->env, env_var)];
			if (env_var && ft_strllen(token->content) > 2)
			{
				env_var = ft_strcut(env_var, '=', '>', 'y');
				token->content = ft_strremplace(token->content, env_var);
			}
			else
				token->content[ft_strllen(token->content) - 1] = '\0';
			token->toktype = env_var_newtoktype(token);
		}
		tokens = tokens->next;
	}
}
