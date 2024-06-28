/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intocomands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/28 19:25:17 by sadoming         ###   ########.fr       */
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
		else if (!ft_strstr(token->content, "-") && checker != 0)
			break ;
		else if (checker == 1)
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
	int		join;

	join = 0;
	tokens = ft_lstgetnode(tokens, *pos);
	//*pos = tokens->pos;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker != 0)
			join = 1;
		if (join)
			cmd->input = push_intoarr(cmd->input, token);
		if (cmd->input[len_of_tokens(cmd->input) - 1]->toktype == SPACE)
			join = 0;
		tokens = tokens->next;
		*pos = *pos + 1;
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
		cmd = fill_comand_flags(cmd, tokens, pos);
		cmd = fill_comand_args(cmd, tokens, pos);
	}
	//cmd = asign_comandtype(cmd); //asign types for utilities
	return (cmd); //23 lines
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
	//Clean comands here or on create?
	tshell->cmd_size = ft_lstsize(tshell->comands);
}
