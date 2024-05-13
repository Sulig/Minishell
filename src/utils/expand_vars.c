/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/13 20:07:28 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*case_of_envvar_exit(char *str, int exit)
{
	size_t	pos;
	char	*env_var;
	char	*result;

	env_var = ft_itoa(exit);
	pos = ft_cnt_tostr(str, "$?");
	result = ft_strinter(str, env_var, pos + 2);
	result = ft_strremove(result, "$?");
	str = ft_free_str(str);
	env_var = ft_free_str(env_var);
	return (result);
}

static char	*expansor_utils(char *str, char **env, char *args)
{
	size_t	pos;
	char	*env_var;
	char	*result;
	char	*tmp;

	env_var = NULL;
	tmp = ft_strdup(args + 1);
	tmp = ft_strjoin_free_fst(tmp, "=");
	env_var = env[ft_search_str(env, tmp)];
	env_var = ft_strcut(env_var, '=', '>', 'y');
	pos = ft_cnt_tostr(str, args) + ft_strllen(args);
	result = ft_strinter(str, env_var, pos);
	result = ft_strremove(result, args);
	tmp = ft_free_str(tmp);
	str = ft_free_str(str);
	return (result);
}

char	*expand_env_var_instr(char *str, char **env, int exit)
{
	char	**args;
	size_t	cnt;

	if (!ft_strstr(str, "$"))
		return (str);
	args = split_intoarr(str);
	if (!args)
		return (str);
	cnt = 0;
	while (args[cnt])
	{
		if (ft_strstr(args[cnt], "$?"))
			str = case_of_envvar_exit(str, exit);
		else
			str = expansor_utils(str, env, args[cnt]);
		cnt++;
	}
	args = ft_auto_free_arr(args);
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
