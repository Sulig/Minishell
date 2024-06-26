/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:19:48 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/18 17:37:10 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Asing comand type:
 * - REDIR	< > << >>
 * - PIPE	|
 * - CMD	the rest
*/
t_cmd	*asign_comandtype(t_cmd *cmd)
{
	if (cmd->cmdtype == PIPE)
		return (cmd);
	if (my_strcmp("<", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">>", cmd->comand))
		cmd->cmdtype = REDIR;
	else if (my_strcmp("<<", cmd->comand))
		cmd->cmdtype = REDIR;
	else
		cmd->cmdtype = CMD;
	return (cmd);
}

static t_list	*free_cmd_error(t_list *comands, t_cmd *cmd)
{
	if (!cmd)
		return (comands);
	cmd->comand = ft_free_str(cmd->comand);
	cmd->input = ft_free_str(cmd->input);
	cmd->options = ft_free_str(cmd->options);
	free(cmd);
	return (comands);
}

static t_cmd	*revise_cmd(t_cmd *cmd)
{
	char	*tmp;
	size_t	cnt;

	if (ft_strllen(cmd->options) || !ft_strchr(cmd->input, '-'))
		return (cmd);
	tmp = ft_strdup(ft_strchr(cmd->input, '-'));
	if (!ft_isalpha(tmp[1]))
		return (cmd);
	cnt = 0;
	while (tmp[++cnt])
		if (tmp[cnt] != '-' && tmp[cnt - 1] != '-')
			tmp[cnt] = '\0';
	cmd->options = ft_strdup(tmp);
	if (ft_strllen(cmd->input + ft_strllen(tmp)) != 0)
		cmd->input = ft_strremplace(cmd->input, cmd->input + ft_strllen(tmp));
	else
		cmd->input = ft_free_str(cmd->input);
	tmp = ft_free_str(tmp);
	tmp = ft_strtrim_s(cmd->input, " ");
	cmd->input = ft_strremplace(cmd->input, tmp);
	tmp = ft_free_str(tmp);
	return (cmd);
}

/*
 * If a REDIR_CMD has an input with spaces && is not quoted
 * Create a comand with this and put it behind the REDIR_CMD
 * Fill the new comand with options && input (if encounters a ' ')
*/
static t_list	*create_comand_behind(t_list *comands, t_cmd *cmd)
{
	t_list	*new_comand;
	t_cmd	*comand;

	if (!ft_strllen(cmd->input) || !ft_strstr(cmd->input, " "))
		return (comands);
	if (cmd->input[0] == '\"' || cmd->input[0] == '\'')
		return (comands);
	comand = ft_calloc(sizeof(t_cmd), 1);
	if (!comand)
		return (comands);
	comand->options = ft_strdup(cmd->options);
	cmd->options = ft_free_str(cmd->options);
	comand->comand = ft_strdup(ft_strchr(cmd->input, ' ') + 1);
	if (ft_strchr(comand->comand, ' '))
		comand->input = ft_strdup(ft_strchr(comand->comand, ' ') + 1);
	comand->comand = ft_strcut(comand->comand, ' ', '<', 'y');
	comand = revise_cmd(comand);
	new_comand = ft_lstnew(comand);
	if (!new_comand)
		return (free_cmd_error(comands, comand));
	new_comand->prev = comands;
	new_comand->next = comands->next;
	comands->next = new_comand;
	return (comands);
}

/*
 * Expand env_var, remove quotes, asign corresponent CMDTYPE (CMD, REDIR || PIPE)
 * Call for create_comand_behind if REDIR->input has ' ' && is no quoted
*/
t_list	*polish_comands(t_shell *tshell, t_list *first, t_list *comands)
{
	t_cmd	*cmd;

	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (cmd->cmdtype == REDIR)
		{
			comands = create_comand_behind(comands, cmd);
			if (ft_strllen(cmd->input))
				if (!(cmd->input[0] == '\'' || cmd->input[0] == '\"'))
					cmd->input = ft_strcut(cmd->input, ' ', '<', 'y');
		}
		cmd = asign_comandtype(cmd);
		cmd = expand_env_vars_cmd(tshell, cmd);
		cmd = clean_comand(cmd);
		cmd = quote_removal(tshell, cmd);
		if (cmd->original && !cmd->input)
			cmd->input = ft_calloc(sizeof(char *), 1);
		comands = comands->next;
	}
	return (first);
}
