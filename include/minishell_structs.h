/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/12 16:11:00 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

enum	e_toktype
{
	TNULL,
	ARGS = 'f',
	ENV = '$',
	OPTION = '-',
	D_QUOTE = 34,
	S_QUOTE = 39,
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	REDIR_DEL,
	REDIR_APP
};

typedef struct s_token
{
	enum e_toktype	toktype;
	char			*content;
	size_t			cont_len;
}					t_token;

typedef struct s_shell
{
	char		**env;
	char		*line;
	t_list		*tokens;
	size_t		tsize;
}				t_shell;

#endif
