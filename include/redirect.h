/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/02 09:04:32 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

# define SAVE 1			// Save mode for save_restore_stdio()
# define RESTORE 0		// Restore mode for save_restore_stdio()
# define OPEN_FILE_MODE 0644
# define READ_END		0				// pipe's read end index
# define WRITE_END		1				// pipe's write end index
# define HEREDOC_FILENAME_PREFIX "/tmp/heredoc_temp_"

void	save_restore_stdio(int std_in, int std_out, int mode);
int		redirect(t_list *cmds, int i);
int		link_output_file(const char *filename, int append);
int		link_input_file(const char *filename);
int		open_file(const char *filename, int flags);
void	pipe_or_die(int fd_pipe[2]);
pid_t	fork_or_die(void);
void	link_read_end(int *fd_pipe);
void	link_write_end(int *fd_pipe);
int		link_heredoc(int n);
int		wait_children(pid_t last_pid, size_t n);
int		read_heredocs(t_list *cmd, int n);
char	*heredoc_filename(int n);
int		read_heredoc(const char *delim, const char *file);
void	clear_heredoc(const char *file);
void	clear_heredocs(int n);
int		read_all_heredocs(t_list **cmds, int cmds_amount);

#endif
