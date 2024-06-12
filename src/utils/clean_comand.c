/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:38:14 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/12 19:18:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_comand_name(t_list *list)
{
	t_token	*token;
	char	*name;

	name = NULL;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->toktype != SPACE)
			name = ft_strjoin_free_fst(name, token->content);
		else if (token->toktype == SPACE && token->location != NO_QUOTED)
			name = ft_strjoin_free_fst(name, token->content);
		else
			break ;
		list = list->next;
	}
	return (name);
}

t_cmd	*clean_comand(t_cmd *cmd)
{
	t_list	*name;

	if (ft_strllen(cmd->comand) || !cmd->comand)
		return (cmd);
	cmd->comand = ft_free_str(cmd->comand);
	name = split_intotokens_forexpand(cmd->input);
	name = fill_token_location(name);
	cmd->comand = create_comand_name(name);
	cmd->input = ft_strremove(cmd->input, cmd->comand);
	name = free_tokens_list(&name);
	cmd = trim_input(cmd);
	return (cmd);
}
