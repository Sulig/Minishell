/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/23 17:29:19 by sadoming         ###   ########.fr       */
=======
/*   Updated: 2024/03/29 19:53:01 by jguillot         ###   ########.fr       */
>>>>>>> Add files via upload
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

/* TOKENS */
enum	e_toktype
{
	TNULL,
	ARGS = 'a',
	CMD = '!',
	ENV = '$',
	FILENAME = 'f',
	OPTION = '-',
	D_QUOTE = 34,
	S_QUOTE = 39,
	PIPE = '|',
	REDIR = '~',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	REDIR_APP,
	REDIR_DEL
};

/* The location of token */
enum	e_location
{
	NO_QUOTED,
	IN_DOUBLE_Q,
	IN_SINGLE_Q
};

/* TOKENS STRUCTURE */
typedef struct s_token
{
	enum e_toktype	toktype;
	enum e_location	location;
	char			*content;
}					t_token;

/* COMANDS STRUCTURE */
typedef struct s_cmd
{
	enum e_toktype	cmdtype;
	char			*comand;
	char			*options;
<<<<<<< HEAD
	char			*input;
}					t_cmd;

/* SAVE THE OUTPUT AND FILE DESCRIPTOR */
typedef struct s_fd
{
	int			st_fd_in;
	int			st_fd_out;
	char		**args;
}				t_fd;

=======
	void			*input;
	void			*output;
	int				build;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

>>>>>>> Add files via upload
/* MINISHELL STRUCTURE */
typedef struct s_shell
{
	int			exit_state;
	char		**env;
	char		**path;
	char		*line;
	t_list		*tokens;
	t_list		*comands;
<<<<<<< HEAD
	t_list		**tree_cmd;
	t_list		*fds;
	pid_t		pid;
	//t_cmd		*act_cmd;
=======
	t_cmd       *cmds;
>>>>>>> Add files via upload
	size_t		tok_size;
	size_t		cmd_size;
}				t_shell;

#endif
