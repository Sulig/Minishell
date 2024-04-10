/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/10 19:47:12 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static enum e_toktype	env_var_newtoktype(t_token *token)
{
	if (my_strcmp("$?", token->content))
		return (ARGS);
	if (ft_strchr(token->content, '$'))
		if (token->location != IN_SINGLE_Q)
			return (ENV);
	return (ARGS);
}

/*
 * !Only for a list of tokens
 * Expand the $var to corresponent in $ENV
 * Do not expand if is inside 'single quotes'
 * Do not expand $?, this will be expanded to the last comand exit_state
*/
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

/*
 * Expand everithing $var to corresponent in $ENV
*/
