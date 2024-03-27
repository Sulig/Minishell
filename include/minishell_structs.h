/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/27 20:14:46 by sadoming         ###   ########.fr       */
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
	void			*output;
}					t_cmd;

/* MINISHELL STRUCTURE */
typedef struct s_shell
{
	int			exit_state;
	char		**env;
	//char		*path;
	char		*line;
	t_list		*tokens;
	t_list		*comands;
	size_t		tok_size;
	size_t		cmd_size;
}				t_shell;

#endif
