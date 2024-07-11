/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_intocomands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:24:02 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/11 19:22:35 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd	*fill_comand_name(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	char	*tmp;
	int		checker;

	cmd->name = duplicate_token((t_token *)tokens->content);
	if (check_beforecreate(NULL, cmd->name) == -1)
	{
		*pos = *pos + 1;
		return (cmd);	
	}
	while (tokens->next)
	{
		tokens = tokens->next;
		*pos = *pos + 1;
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1 || !checker)
			break ;
		tmp = cmd->name->content;
		cmd->name->content = ft_strjoin_free_fst(tmp, token->content);
	}
	return (cmd);
}

static t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	tokens = ft_search_nodebypos(tokens, *pos);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1)
			break ;
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

static t_cmd	*fill_comand_args(t_cmd *cmd, t_list *tokens, size_t *pos, int br)
{
	t_token	*token;
	int		checker;

	tokens = ft_search_nodebypos(tokens, *pos);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(NULL, token);
		if (checker == -1 || (!checker && br))
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
	cmd = fill_comand_name(cmd, tokens, pos);
	tokens = ft_search_nodebypos(tokens, *pos);
	if (tokens)
		token = (t_token *)tokens->content;
	if (cmd->cmdtype == REDIR)
	{
		tokens = jump_tocontent(tokens, pos);
		cmd = fill_comand_args(cmd, tokens, pos, 1);
		*pos = *pos + 1;
	}
	else if (cmd->cmdtype != PIPE && check_beforecreate(NULL, token) != -1)
	{
		*pos = *pos + 1;
		cmd = fill_comand_flags(cmd, tokens, pos);
		cmd = fill_comand_args(cmd, tokens, pos, 0);
	}
	select_nextpos(cmd, token, pos);
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
