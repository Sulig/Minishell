/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:59:06 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/01 21:00:26 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Reads the here document for the 'n'-th command, assuming 'str' is the word
// right next to the << token.
// Returns 0 on success, or -1 in case of failure (setting errno).
static int	read_heredoc_n(const char *str, int n)
{
	char	*delimiter;
	char	*file;
	int		exit_status;

	delimiter = ft_strdup(str);
	file = heredoc_filename(n);
	exit_status = read_heredoc(delimiter, file);
	free(delimiter);
	free(file);
	return (exit_status);
}

// Reads the here documents for 'cmd' from left to right, into a temp file
// knowing it's the 'n'-th command.
// If there's more than one here document, the previous ones are overwritten.
// Returns 0 on success. Otherwise, returns a non-zero value.
int	read_heredocs(t_list *cmds, int n)
{
	t_list	*node;
	int		exit_status;
	t_cmd	*cmd;

	node = cmds;
	while (node)
	{
		cmd = node->content;
		if (cmd->cmdtype == REDIR && !ft_strncmp(cmd->comand, "<<", 3))
		{
			exit_status = read_heredoc_n(cmd->input, n);
			if (exit_status)
				return (exit_status);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
