/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/23 17:47:38 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_beforecreate(t_shell *tshell, t_token *token)
{
	if (!token)
	{
		if (!check_valid_syntax(tshell))
			return (0);
		if (!tshell->tokens)
			return (0);
		if (!checkfor_unclosedquotes(tshell, tshell->tokens))
			return (0);
		expand_env_var(tshell);
		return (1);
	}
	if (token->toktype == PIPE || token->toktype == REDIR)
		if (token->location == NO_QUOTED)
			return (-1);
	if (token->toktype == ARGS)
		return (1);
	if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
		return (4);
	if (token->toktype == ENV && token->location == IN_SINGLE_Q)
		return (1);
	if (token->toktype == SPACE && token->location != NO_QUOTED)
		return (1);
	if (token->toktype == OPTION && token->location == NO_QUOTED)
		return (3);
	return (0);
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
		else if (check_beforecreate(NULL, token) == 3 && tokens->next)
		{
			*pos = *pos + 1;
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			cmd->options = ft_strdup(token->content);
		}
		else
			cmd->input = ft_strjoin_free_fst(cmd->input, token->content);
	}
	return (cmd);
}

static t_cmd	*fill_comand_name(t_list *tokens, t_cmd *cmd, size_t *pos)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	cmd->comand = NULL;
	if (token->toktype == PIPE || token->toktype == REDIR)
	{
		cmd->comand = ft_strdup(token->content);
		return (cmd);
	}
	if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
		token->toktype = ARGS;
	while (tokens && check_beforecreate(NULL, token) > 0)
	{
		cmd->comand = ft_strjoin_free_fst(cmd->comand, token->content);
		tokens = tokens->next;
		*pos = *pos + 1;
		if (tokens)
			token = (t_token *)tokens->content;
	}
	if (tokens && (token->toktype == PIPE || token->toktype == REDIR))
		*pos = *pos -1;
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
		cmd = fill_command(cmd, tokens, pos);
		cmd->options = ft_strjoin_free_sec("-", cmd->options);
		cmd = trim_input(cmd);
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

	pos = 0;
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
	tshell->comands = polish_comands(tshell, tshell->comands, tshell->comands);
	tshell->cmd_size = ft_lstsize(tshell->comands);
}
