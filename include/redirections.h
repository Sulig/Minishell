/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:45:25 by jguillot          #+#    #+#             */
/*   Updated: 2024/03/28 21:39:31 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# define SAVE 1			// Save mode for save_restore_stdio()
# define RESTORE 0		// Restore mode for save_restore_stdio()

# define BUILT_ECHO 0
# define BUILT_PWD 1
# define BUILT_ENV 2

# define BUILT_CD 10
# define BUILT_UNSET 12

# define BUILT_EXPORT 20
# define BUILT_EXIT 23

# define OPEN_FILE_MODE 0644

typedef struct s_pipe
{
	int	cmds_amount;
	int	prev_fds[2];
	int	next_fds[2];
	int	i;
}	t_pipe;

/* REDIRECTIONS */
void	redirections(t_shell *tshell);
void	save_restore_stdio(int std_in, int std_out, int mode);
int		redirect(t_cmd *cmd, int n);
int		link_output_file(const char *filename, int append);
int		open_file(const char *filename, int flags);
int		link_input_file(const char *filename);
int		execute_builtin(t_shell *tshell, int child);
char	**get_args_from_cmd(t_cmd *cmd);

/* REDIRECTIONS_UTILS */
int		is_builtin_name(const char *str);
void	arrstr_free(char **arr);

//TESTING
char**	splitString(char *input, int *count);
t_cmd	*arrayToList(char **words, int count);

//BUILDINS
int		set_builtin(t_cmd *cur);
#endif