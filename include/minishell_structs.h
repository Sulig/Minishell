/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/13 19:55:38 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

enum	e_toktype
{
	TNULL,
	ARGS = 'f',
	CMD = '!',
	ENV = '$',
	OPTION = '-',
	D_QUOTE = 34,
	S_QUOTE = 39,
	PIPE = '|',
	REDIR = '~',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	REDIR_DEL,
	REDIR_APP
};

enum	e_location
{
	NO_QUOTED,
	IN_DOUBLE_Q,
	IN_SINGLE_Q
};

typedef struct s_token
{
	enum e_toktype	toktype;
	enum e_location	location;
	char			*content;
}					t_token;

typedef struct s_cmd
{
	enum e_toktype	toktype;
	char			*comand;
	char			*options;
	void			*input;
	void			*output;
}					t_cmd;

typedef struct s_shell
{
	char		**env;
	char		*line;
	t_list		*tokens;
	t_list		*comands;
	size_t		tok_size;
	size_t		cmd_size;
}				t_shell;

#endif
