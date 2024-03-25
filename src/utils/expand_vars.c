/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/25 18:12:37 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			if (env_var)
			{
				env_var = ft_strcut(env_var, '=', '>', 'y');
				token->content = ft_strremplace(token->content, env_var);
				token->toktype = ARGS;
			}
		}
		tokens = tokens->next;
	}
}
