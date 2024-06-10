/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/28 17:43:42 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
static char	*consider_envcase(char *result, t_token *token)
{
	if (ft_strstr(token->content, "$?") && token->location != IN_SINGLE_Q)
	{
		result = ft_strjoin_free_fst(result, "\1");
		result = ft_strjoin_free_fst(result, token->content);
		result = ft_strjoin_free_fst(result, "\1");
	}
	else
		result = ft_strjoin_free_fst(result, token->content);
	return (result);
}*/

static char	*convert_tokens_instr(t_list *tokens)
{
	char	*result;
	t_token	*token;

	result = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ARGS || token->toktype == OPTION)
			result = ft_strjoin_free_fst(result, token->content);
		else if (token->toktype == SPACE)
			result = ft_strjoin_free_fst(result, token->content);
		else if (token->toktype == ENV)
			result = ft_strjoin_free_fst(result, token->content);
		else if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
			if (token->location != NO_QUOTED)
				result = ft_strjoin_free_fst(result, token->content);
		tokens = tokens->next;
	}
	return (result);
}

static t_cmd	*quote_removal_options(t_shell *tshell, t_cmd *cmd)
{
	if (ft_strchr(cmd->options, '\"') || ft_strchr(cmd->options, '\''))
	{
		free_tokens(tshell);
		tshell->line = cmd->options;
		split_intotokens(tshell);
		cmd->options = ft_free_str(cmd->options);
		cmd->options = convert_tokens_instr(tshell->tokens);
	}
	return (cmd);
}

/*
 * Removes all quotes of comand
 * * Considers cases like: "''" && '""' and so on..
*/
t_cmd	*quote_removal(t_shell *tshell, t_cmd *cmd)
{
	tshell->line = ft_free_str(tshell->line);
	if (ft_strchr(cmd->comand, '\"') || ft_strchr(cmd->comand, '\''))
	{
		free_tokens(tshell);
		tshell->line = cmd->comand;
		split_intotokens(tshell);
		cmd->comand = ft_free_str(cmd->comand);
		cmd->comand = convert_tokens_instr(tshell->tokens);
	}
	if (ft_strchr(cmd->input, '\"') || ft_strchr(cmd->input, '\''))
	{
		free_tokens(tshell);
		tshell->line = cmd->input;
		split_intotokens(tshell);
		cmd->input = ft_free_str(cmd->input);
		cmd->input = convert_tokens_instr(tshell->tokens);
	}
	cmd = quote_removal_options(tshell, cmd);
	tshell->line = NULL;
	return (cmd);
}
