/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/14 15:56:25 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Creates a here document, reading the standard input until 'd' is found and
// saving the content into the specified temp 'file'.
// If 'x' is TRUE, the variable names are expanded.
// Exits with 0 on success, 1 on SIGINT received, or -1 in case of failure.
static int	read_hd_child(char *d, const char *file, char **env)
{
	int		fd_file;

	set_signals(HERE);
	fd_file = open_file(file, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd_file == -1)
		return (print_comun_error("cannot create temp file for here document", EXIT_FAILURE));
	heredoc(env, d, fd_file);
	exit(close(fd_file));
}

// Creates a here document, reading the standard input until 'delim' is found
// and saving the content into the specified temp 'file'.
// Returns 0 on success, 1 on SIGINT received, or -1 in case of failure.
int	read_heredoc(char *delim, const char *file, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
		read_hd_child(delim, file, env);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

// Reads the here document for the 'n'-th command, assuming 'str' is the
// delimiter
// Returns 0 on success, or -1 in case of failure
static int	read_heredoc_n(char *str, int n, char **env)
{
	char	*delim;
	char	*file;
	int		exit_status;

	delim = ft_strdup(str);
	file = heredoc_filename(n);
	exit_status = read_heredoc(delim, file, env);
	free(delim);
	free(file);
	return (exit_status);
}

// Reads the here documents for 'cmd' from left to right, into a temp file
// knowing it's the 'n'-th command.
// If there's more than one here document, the previous ones are overwritten.
// Returns 0 on success. Otherwise, returns a non-zero value.
int	read_heredocs(t_list *cmds, int n, char **env)
{
	t_list	*node;
	t_cmd	*cmd;
	int		err;

	node = cmds;
	while (node)
	{
		cmd = node->content;
		if (cmd->cmdtype == REDIR && !ft_strncmp(cmd->comand, "<<", 3))
		{
			err = read_heredoc_n(cmd->options, n, env);
			if (err)
				return (err);
			node = node->next;
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

// Reads all the here documents from the array of commands 'cmds', from left
// to right, into the appropriate temp files to be read afterwards.
// Returns 0 on success. Otherwise, returns a non-zero value.
int	read_all_heredocs(t_list **cmds, int cmds_amount, char **env)
{
	int		i;
	int		exit_status;

	stop_signals();
	i = -1;
	while (++i < cmds_amount)
	{
		exit_status = read_heredocs(cmds[i], i, env);
		if (exit_status)
			return (exit_status);
	}
	return (0);
}
