/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:03:35 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/17 19:34:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*join_option(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens->next)
		return (cmd);
	tokens = tokens->next;
	token = (t_token *)tokens->content;
	if (token->toktype == OPTION)
		return (cmd);
	cmd->options = ft_strjoin_free_fst(cmd->options, "-");
	cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
	if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
	{
		while (tokens->next)
		{
			*pos = *pos + 1;
			tokens = tokens->next;
			token = (t_token *)tokens->content;
			if (token->toktype == D_QUOTE || token->toktype == S_QUOTE)
				break ;
			cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
		}
		cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
	}
	*pos = *pos + 1;
	return (cmd);
}

static int	consider_specialcase(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->toktype != OPTION)
		return (0);
	while (tokens->next)
	{
		tokens = tokens->next;
		token = (t_token *)tokens->content;
		if (token->toktype == SPACE)
			break ;
		if (token->toktype == OPTION || ft_strstr(token->content, "-"))
			return (1);
	}
	return (0);
}

t_cmd	*fill_comand_options(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;
	int		checker;

	if (!tokens)
		return (cmd);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		checker = check_beforecreate(0, token);
		if (token->toktype == SPACE)
			cmd->options = ft_strjoin_free_fst(cmd->options, token->content);
		else if (checker == -1 || checker == 1 || consider_specialcase(tokens))
		{
			*pos = *pos - 1;
			break ;
		}
		else if (checker == 3)
		{
			cmd = join_option(cmd, tokens, pos);
			tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
		}
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}

t_cmd	*fill_comand_input(t_cmd *cmd, t_list *tokens, size_t *pos)
{
	t_token	*token;

	if (!tokens)
		return (cmd);
	if ((*pos >= ft_lstsize(tokens) && !cmd->options) || *pos < tokens->pos)
		*pos = tokens->pos;
	else if (*pos > tokens->pos)
		tokens = ft_lstgetnode(tokens, *pos - tokens->pos);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (check_beforecreate(NULL, token) == -1)
		{
			*pos = *pos - 1;
			break ;
		}
		else
			cmd->input = ft_strjoin_free_fst(cmd->input, token->content);
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (cmd);
}
