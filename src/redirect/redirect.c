/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:19:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/18 17:23:15 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Performs the redirection defined by 'redir',
 * taking 'next' as the following token, knowing it's the 'n'-th command.
 * In the case of here documents, quote-removal is performed.
 * Returns the appropriate exit code after printing any error message.
*/
static int	redirect_one(t_cmd *redir, int n)
{
	char	*str;

	if (redir->input == NULL)
	{
		print_err_custom("ambiguous redirect", 1);
		return (EXIT_FAILURE);
	}
	str = redir->input;
	if (!ft_strncmp(redir->comand, ">", 2))
		return (link_output_file(str, FALSE));
	else if (!ft_strncmp(redir->comand, ">>", 3))
		return (link_output_file(str, TRUE));
	else if (!ft_strncmp(redir->comand, "<", 2))
		return (link_input_file(str));
	else if (!ft_strncmp(redir->comand, "<<", 3))
		return (link_heredoc(n));
	return (EXIT_FAILURE);
}

/*
* Performs all redirections of 'cmd', from left-to-right, removing the
* redirection tokens, knowing it's the 'n'-th command. Returns the exit status.
* If a redirection error ocurrs, prints an error message.
*/
int	redirect(t_list *cmds, int n)
{
	int		exit_stat;
	t_list	*node;
	t_cmd	*cmd;

	exit_stat = 0;
	node = cmds;
	while (node && exit_stat == 0)
	{
		cmd = node->content;
		if (cmd->cmdtype == REDIR)
		{
			exit_stat = redirect_one(cmd, n);
			node = node->next;
		}
		else
			node = node->next;
	}
	return (exit_stat);
}
