/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/25 14:07:37 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_beforecreate(t_shell *tshell)
{
	if (!check_valid_syntax(tshell))
		return (0);
	if (!checkfor_unclosedquotes(tshell, tshell->tokens))
		return (0);
	expand_env_var(tshell);
	return (1);
}

t_cmd	*create_command(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmdtype = token->toktype;
	if (cmd->cmdtype == ARGS)
		cmd->cmdtype = CMD; 
	cmd->comand = token->content;
	return (cmd);
}

t_cmd	*fill_command(t_cmd *cmd, t_list *tokens)
{
	t_token	*token;
	while (tokens->next)
	{
		tokens = tokens->next;
		token = (t_token *)tokens->content;
		if (token->toktype == PIPE || token->toktype == REDIR)
			break ;
		if (token->toktype == OPTION && tokens->next)
		{
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			cmd->options = token->content;
		}
	}
	return (cmd);
}

void	split_intocomands(t_shell *tshell, t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;

	if (!check_beforecreate(tshell))
		return ;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->toktype == ARGS)
		{
			tmp = ft_lstnew(create_command(token));
			if (tmp)
				tmp->content = fill_command((t_cmd *)tmp->content, tokens);
		}
		else if (token->toktype == PIPE || token->toktype == REDIR)
			tmp = ft_lstnew(create_command(token));
		if (tmp)
			ft_lstadd_back(&tshell->comands, tmp);
		tokens = tokens->next;
	}
}
