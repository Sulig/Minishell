/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/07 19:49:58 by sadoming         ###   ########.fr       */
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
	D_QUOTE = '"',
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
}					t_token;

typedef struct s_shell
{
	char		**env;
	char		*line;
	t_list		*tokens;
	int			d_quote;
	size_t		tsize;
}				t_shell;

#endif
