/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 09:57:20 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Creates a here document, reading the standard input until 'd' is found and
* saving the content into the specified temp 'file'.
* If 'x' is TRUE, the variable names are expanded.
* Exits with 0 on success, 1 on SIGINT received, or -1 in case of failure.
*/
static int	read_hd_child(char *d, const char *file, t_shell *tshell)
{
	int		fd_file;

	set_signals(HERE);
	fd_file = open_file(file, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd_file == -1)
		return (print_comun_error("cannot create temp file for here document", EXIT_FAILURE));
	heredoc(tshell, d, fd_file);
	close(fd_file);
	return tshell->exit_state;
}

/*
* Creates a here document, reading the standard input until 'delim' is found
* and saving the content into the specified temp 'file'.
* Returns 0 on success, 1 on SIGINT received, or -1 in case of failure.
* pid_t wait(int *status);-> It suspends execution of the calling process until
* a child specified by pid argument has changed state
* WIFEXITED and WEXITSTATUS are two of the options which can be used to know
* the exit status of the child.
* WIFEXITED(status) : returns true if the child terminated normally.
* WEXITSTATUS(status) : returns the exit status of the child. This macro should be
* employed only if WIFEXITED returned true.
*/
int	read_heredoc(char *delim, const char *file, t_shell *tshell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
		read_hd_child(delim, file, tshell);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
	return (0);
}

/*
* Reads the here document for the 'n'-th command, assuming 'str' is the
* delimiter
* Returns 0 on success, or -1 in case of failure
*/
static int	read_heredoc_n(char *str, int n, t_shell *tshell)
{
	char	*delim;
	char	*file;
	int		exit_status;

	delim = ft_strdup(str);
	file = heredoc_filename(n);
	exit_status = read_heredoc(delim, file, tshell);
	free(delim);
	free(file);
	return (exit_status);
}

/*
* Reads the here documents for 'cmd' from left to right, into a temp file
* knowing it's the 'n'-th command.
* If there's more than one here document, the previous ones are overwritten.
* Returns 0 on success. Otherwise, returns a non-zero value.
*/
int	read_heredocs(t_list *cmds, int n, t_shell *tshell)
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
			err = read_heredoc_n(cmd->input, n, tshell);
			if (err)
				return (err);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

/*
* Reads all the here documents from the array of commands 'cmds', from left
* to right, into the appropriate temp files to be read afterwards.
* Returns 0 on success. Otherwise, returns a non-zero value.
*/
int	read_all_heredocs(t_list **cmds, int cmds_amount, t_shell *tshell)
{
	int		i;
	int		exit_status;

	stop_signals();
	i = -1;
	while (++i < cmds_amount)
	{
		exit_status = read_heredocs(cmds[i], i, tshell);
		if (exit_status)
			return (exit_status);
	}
	return (0);
}
