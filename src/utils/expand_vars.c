/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/08 19:59:29 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_env_var_instr(char *str, char **env, int exit)
{
	char	*search;
	char	*tmp;
	char	*env_var;

	(void)exit;
	if (!ft_strstr(str, "$"))
		return (str);
	//consider case $?
	tmp = ft_strstr(str, "$");
	tmp[ft_cnttoch_out(tmp, ' ')] = '\0';
	search = ft_strjoin_s(tmp + 1, "=");
	env_var = env[ft_search_str(env, search)];
	//cut env
	//integrate env next to $
	str = ft_strremove(str, tmp);
	search = ft_free_str(search);
	return (str);
	//return (expand_env_var_instr(str, env, exit));
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
