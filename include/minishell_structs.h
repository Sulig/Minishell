/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/06 19:51:07 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

enum	e_toktype
{
	ARGS,
	ENV,
	OPTION,
	D_QUOTE,
	S_QUOTE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_DEL,
	REDIR_APP,
	TNULL
};

typedef struct s_token
{
	enum e_toktype	toktype;
	char			*comand;
	char			**options;
	char			*args;
}					t_token;

typedef struct s_shell
{
	char		**env;
	t_list		*tokens;
	size_t		tsize;
}				t_shell;

#endif
