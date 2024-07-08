/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intocomands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/08 17:32:16 by sadoming         ###   ########.fr       */
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
		if (checkfor_unclosedquotes(tshell, tshell->tokens) == 2)
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

static t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker == 1)
			break ;
		else if (ft_cnt_tostr(token->content, "-") > 0 && checker != 0)
			break ;
		else if (ft_strstr(token->content, "-"))
			cmd->flags = push_intoarr(cmd->flags, token);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}

static t_cmd	*fill_comand_args(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	tokens = ft_search_nodebypos(tokens, *pos);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		cmd->input = push_intoarr(cmd->input, token);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	if (cmd->input)
		cmd->input = clean_array(cmd->input);
	return (cmd);
}

static t_cmd	*create_command(t_list *tokens, t_token *token, size_t *pos)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmdtype = token->toktype;
	cmd->name = duplicate_token(token);
	tokens = tokens->next;
	if (tokens)
		token = (t_token *)tokens->content;
	if (cmd->cmdtype == REDIR)
	{
		token = jump_tocontent(tokens, pos);
		cmd->input = push_intoarr(cmd->input, token);
		*pos = *pos + 1;
	}
	else if (cmd->cmdtype != PIPE && token->toktype != PIPE)
	{
		*pos = *pos + 1;
		cmd = fill_comand_flags(cmd, tokens, pos);
		cmd = fill_comand_args(cmd, tokens, pos);
	}
	cmd = asign_comandtype(cmd);
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
			tokens = ft_search_nodebypos(tokens, pos);
		}
		if (tokens)
			tokens = tokens->next;
	}
	expand_and_unquote(tshell, tshell->comands);
	tshell->cmd_size = ft_lstsize(tshell->comands);
}
