/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:19:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/07/07 12:54:38 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Performs the redirection defined by 'redir',
 * taking 'next' as the following token, knowing it's the 'n'-th command.
 * In the case of here documents, quote-removal is performed.
 * Returns the appropriate exit code after printing any error message.
*/
static int	redirect_one(char **arr, char *comand, int n)
{
	if (arr == NULL)
	{
		print_err_custom("ambiguous redirect", 1);
		return (EXIT_FAILURE);
	}
	if (!ft_strncmp(comand, ">", 2))
		return (link_output_file(arr[0], FALSE));
	else if (!ft_strncmp(comand, ">>", 3))
		return (link_output_file(arr[0], TRUE));
	else if (!ft_strncmp(comand, "<", 2))
		return (link_input_file(arr[0]));
	else if (!ft_strncmp(comand, "<<", 3))
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
	char	**args;
	char	*comand;

	args = NULL;
	exit_stat = 0;
	node = cmds;
	while (node && exit_stat == 0)
	{
		cmd = node->content;
		if (cmd->cmdtype == REDIR)
		{
			args = get_arr_input_from_cmd(cmd);
			comand = get_name_from_cmd(cmd);
			exit_stat = redirect_one(args, comand, n);
			free_arr_2d(args);
			free(comand);
			node = node->next;
		}
		else
			node = node->next;
	}
	return (exit_stat);
}
