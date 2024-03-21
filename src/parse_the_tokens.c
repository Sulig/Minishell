/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/21 20:13:13 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_env_var(t_shell *tshell)
{
	t_list	*tokens;
	t_token	*token;
	char	*env_var;
	int		quoted;

	tokens = tshell->tokens;
	quoted = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		env_var = token->content + 1;
		env_var = tshell->env[ft_search_str(tshell->env, env_var)];
		ft_printf("Gotted: %s\n", env_var);
		tokens = tokens->next;
	}
}

void	split_intocomands(t_shell *tshell)
{
	if (!check_valid_syntax(tshell))
		return ;
	if (!checkfor_unclosedquotes(tshell, tshell->tokens))
		return ;
	print_all_arrstr(tshell->env);
	expand_env_var(tshell);
}
