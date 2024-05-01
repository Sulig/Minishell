/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:34:35 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/01 20:59:37 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Creates a here document, reading the standard input until 'd' is found and
// saving the content into the specified temp 'file'.
// Exits with 0 on success, 1 on SIGINT received, or -1 in case of failure.
static int	read_hd_child(const char *d, const char *file)
{
	int		fd_file;
	char	*line;

	set_signals(HERE);
	fd_file = open_file(file, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd_file == -1)
		return (print_comun_error(MSG_HEREDOC_ERR, EXIT_FAILURE));
	while (1)
	{
		line = readline(HEREDOC);
		if (line == NULL)
			ft_putstr_fd("\033[A\033[2K> ", STDOUT_FILENO);
		if (line == NULL || !ft_strncmp(line, d, ft_strlen(d) + 1))
			break ;
		ft_putendl_fd(line, fd_file);
	}
	exit(close(fd_file));
}

// Creates a here document, reading the standard input until 'delim' is found
// and saving the content into the specified temp 'file'.
// Returns 0 on success, 1 on SIGINT received, or -1 in case of failure.
int	read_heredoc(const char *delim, const char *file)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
		read_hd_child(delim,file);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
