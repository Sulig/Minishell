/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:28 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:42 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

# define SAVE 1
# define RESTORE 0
# define OPEN_FILE_MODE 0644

void	save_restore_stdio(t_shell *tshell, int std_in, int std_out, int mode);
int		redirect(t_list *cmd);
int     link_input_file(const char *filename);
int		link_output_file(const char *filename, int append);
int		open_file(const char *filename, int flags);

#endif
