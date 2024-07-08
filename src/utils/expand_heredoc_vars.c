/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:15:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/25 16:15:12 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expansor_utils(char *str, char **env, int exit)
{
	char	*env_var;
	char	*tmp;
	char	*itoa;

	if (ft_strstr(str, "$?"))
	{
		itoa = ft_itoa(exit);
		tmp = ft_strinter(str, itoa, ft_cnt_tostr(str, "$?") + 2);
		str = ft_free_str(str);
		itoa = ft_free_str(itoa);
		tmp = ft_strremove(tmp, "$?");
		return (tmp);
	}
	env_var = NULL;
	tmp = ft_strdup(str + 1);
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

/*
 * Expands the str.
 * 1. Create a list of tokens
 * 2. Expand each token
 * 3. Join again in str
 *
 * Proceed with caution, this expansor works like expansor for heredoc.
 * It won't mind if is inside of simple quotes
*/
char	*expand_heredoc_vars(char *str, char **env, int exit)
{
	t_list	*tokens;
	t_list	*first;
	t_token	*token;

	if (!ft_strstr(str, "$"))
		return (str);
	tokens = splitline_intotokens(str);
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
