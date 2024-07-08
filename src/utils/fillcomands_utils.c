/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillcomands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/08 18:41:49 by sadoming         ###   ########.fr       */
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
	if (my_strcmp("<", cmd->name->content))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">", cmd->name->content))
		cmd->cmdtype = REDIR;
	else if (my_strcmp(">>", cmd->name->content))
		cmd->cmdtype = REDIR;
	else if (my_strcmp("<<", cmd->name->content))
		cmd->cmdtype = REDIR;
	else
		cmd->cmdtype = CMD;
	return (cmd);
}

/*
** Skips Spaces ->
*	Look to tthe content, if toktype is " " go to next
*	and so on, until finds a other content or no more nodes.
*/
t_token	*jump_tocontent(t_list *tokens, size_t *pos)
{
	t_token	*token;

	token = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (check_beforecreate(NULL, token) != 0)
			break ;
		tokens = tokens->next;
		*pos = *pos + 1;
	}
	return (token);
}

/*
** Remove duplicated SPACE into array
*/
t_token	**clean_array(t_token **tokens)
{
	size_t	j;

	j = -1;
	if (tokens[0]->toktype == SPACE)
	{
		tokens = clear_tarr(tokens);
		return (tokens);
	}
	while (tokens[++j])
	{
		if (tokens[j]->toktype == SPACE && tokens[j + 1])
		{
			if (tokens[j + 1]->toktype == SPACE)
			{
				tokens = pop_outarr(tokens, j);
				j = -1;
			}
		}
		if (!tokens)
			return (tokens);
	}
	if (tokens)
		if (tokens[len_of_tokens(tokens) - 1]->toktype == SPACE)
			tokens = pop_outarr(tokens, len_of_tokens(tokens) - 1);
	return (tokens);
}

/*
** Expand enviroment variables & remove quotes
*	In Unquoting, removes the quotes
*		* The unquoter will asing the location with the quote encountered.
*		* NO_QUOTED || IN_SINGLE_Q '' || IN_DOUBLE_Q ""
*		* By deffault, if no quote encountered the location is NO_QUOTED
*		* If encounters a env_var && can expand
*			** The toktype will be ENV (so it can expand later)
*	In expansor, expands the enviroment variables
*		* If the variable is inside of '' -> do not expand
*		* If encounters a $? && expand is 1 -> expand to tshell->exit_state
*		** The last rule is affected by LOCATION too
*/
void	expand_and_unquote(t_shell *tshell, t_list *comands)
{
	t_cmd	*cmd;

	if (!tshell->comands)
		return ;
	while (comands)
	{
		cmd = (t_cmd *)comands->content;
		if (cmd->cmdtype != PIPE)
		{
			cmd = quote_removal(cmd);
			cmd = expand_env_vars_cmd(tshell, cmd, 0);
		}
		comands = comands->next;
	}
}
