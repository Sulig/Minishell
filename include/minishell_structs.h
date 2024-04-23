/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/23 20:03:36 by sadoming         ###   ########.fr       */
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
	char			*input;
}					t_cmd;

/* SAVE THE OUTPUT AND FILE DESCRIPTOR */
typedef struct s_fd
{
	int			st_fd_in;
	int			st_fd_out;
	char		**args;
}				t_fd;

/* MINISHELL STRUCTURE */
typedef struct s_shell
{
	int			exit_state;
	char		**env;
	char		**path;
	char		*line;
	t_list		*tokens;
	t_list		*comands;
	t_list		**tree_cmd;
	t_list		*fds;
	pid_t		pid;
	//t_cmd		*act_cmd;
	size_t		tok_size;
	size_t		cmd_size;
}				t_shell;

#endif
