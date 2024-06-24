/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intocomands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/24 17:07:57 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * This function have 2 parts:
 * 	- Part 1 -> Check valid syntax && no closed quotes in tshell
 * 	- Part 2 -> Token->toktype Checker
 * 		- -1	|> PIPES && REDIRS (NO_QUOTED)
 * 		- 1		|> ARGS && SPACES (IN_QUOTES)
 * 		- 2		|> QUOTES
 * 		- 3		|> FLAGS (NO QUOTED)
 * 		- 0		|> ETC..
*/
int	check_beforecreate(t_shell *tshell, t_token *token)
{
	if (!token)
	{
		if (!tshell->tokens)
			return (0);
		if (check_valid_syntax(tshell) == 2)
			return (0);
		if (!checkfor_unclosedquotes(tshell, tshell->tokens))
			return (0);
		return (1);
	}
	if (token->toktype == PIPE || token->toktype == REDIR)
		if (token->location == NO_QUOTED)
			return (-1);
	if (token->toktype == ARGS || token->toktype == ENV)
		return (1);
	if (token->toktype == SPACE && token->location != NO_QUOTED)
		return (1);
	if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
		return (2);
	if (token->toktype == FLAG && token->location == NO_QUOTED)
		return (3);
	return (0);
}

static t_cmd	*fill_comand_name(t_list *tokens, t_cmd *cmd, size_t *pos)
{
	t_token	*token;
	char	*tmp;

	token = (t_token *)tokens->content;
	tmp = NULL;
	if (token->toktype == PIPE || token->toktype == REDIR)
	{
		cmd->comand->content = ft_strdup(token->content);
		return (cmd);
	}
	while (tokens && check_beforecreate(NULL, token) > 0)
	{
		tmp = ft_strjoin_free_fst(tmp, token->content);
		tokens = tokens->next;
		*pos = *pos + 1;
		if (tokens)
			token = (t_token *)tokens->content;
	}
	if (tokens && (token->toktype == PIPE || token->toktype == REDIR))
		*pos = *pos -1;
	cmd->comand->content = tmp;
	return (cmd);
}

static t_cmd	*fill_command(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens)
		return (cmd);
	while (tokens->next)
	{
		*pos = *pos + 1;
		tokens = tokens->next;
		token = (t_token *)tokens->content;
		if (check_beforecreate(NULL, token) == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		else
		{
			cmd = fill_comand_flags(cmd, tokens, pos);
			//cmd = fill_comand_input(cmd, tokens, pos);
			tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
			if (!tokens)
				break ;
		}
	}
	return (cmd);
}

static t_cmd	*create_command(t_list *tokens, t_token *token, size_t *pos)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmdtype = token->toktype;
	cmd = fill_comand_name(tokens, cmd, pos);
	tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
	if (tokens)
		token = (t_token *)tokens->content;
	if (token->toktype != PIPE)
	{
		//fill cmd -> original (tokens input)
		cmd = fill_command(cmd, tokens, pos);
		//create **input spliting original -> [0][hello] [1]["Exemple   template"]
		//trim && clean: comand name && flags
		//asign types for utilities
		cmd = asign_comandtype(cmd);
	}
	return (cmd);
}

void	split_intocomands(t_shell *tshell, t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;
	size_t	pos;
	int		checker;

	tmp = NULL;
	if (!check_beforecreate(tshell, NULL))
		return ;
	while (tokens)
	{
		pos = ft_lstpos_node(tshell->tokens, tokens);
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker > 0 || checker == -1)
		{
			tmp = ft_lstnew(create_command(tokens, token, &pos));
			ft_lstadd_back(&tshell->comands, tmp);
			tokens = ft_lstgetnode(tshell->tokens, pos);
		}
		if (tokens)
			tokens = tokens->next;
	}
	//Clean comands?
	tshell->cmd_size = ft_lstsize(tshell->comands);
}
