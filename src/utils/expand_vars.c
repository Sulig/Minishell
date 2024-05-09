/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/09 20:05:23 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Expand '$?' to exit state
*/
static char	*case_of_envvar_exit(char *str, int exit)
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

/*
 * Expand the var
*/
static char	*expansor_utils(char *str, char *env_var)
{
	size_t	pos;
	char	*result;
	char	*remove;

	remove = ft_strdup(ft_strstr(str, "$"));
	remove[ft_cnttoch_out(remove, ' ')] = '\0';
	env_var = env[ft_search_str(env, search)];
	env_var = ft_strcut(env_var, '=', '>', 'y');
	pos = ft_cnt_tostr(str, remove) + ft_strllen(remove);
	result = ft_strinter(str, env_var, pos);
	result = ft_strremove(result, remove);
	remove = ft_free_str(remove);
	str = ft_free_str(str);
	return (result);
}

char	*expand_env_var_instr(char *str, char **env, int exit)
{
	/*
	 * For next change, try: 
	 * 1. split(str, ' ');
	 * 2. Expand each case
	 * 	2.1 Ignore case '$' && normal text
	 * 	2.2 Expand case '$?' to exit -> use case_of_envvar_exit
	 * 	2.3 Expand if encounters the var, else remplace for "".
	 * 3. Join again
	*/
	char	**args;
	size_t	cnt;

	if (!ft_strstr(str, "$"))
		return (str);
	args = ft_split(str, ' ');
	if (!args)
		return (str);
	str = ft_free_str(str);
	cnt = 0;
	while (args[cnt])
	{
		if (ft_strstr(args[cnt], "$?"))
			args[cnt] = case_of_envvar_exit(args[cnt], exit);
		// Ignore case '$'
		// expand
		cnt++;
	}
	// Join
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
