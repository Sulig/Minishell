/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:09:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/21 16:24:04 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

# define HEREDOC_FILENAME_PREFIX "/tmp/heredoc_temp_"

int		read_all_heredocs(t_list **cmds, int cmds_amount, t_shell *tshell);
int		read_heredocs(t_list *cmds, int n, t_shell *tshell);
char	*heredoc_filename(int n);
void	clear_heredocs(int n);
int		link_heredoc(int n);

#endif
