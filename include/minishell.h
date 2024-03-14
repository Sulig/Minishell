/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:56:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/14 19:51:58 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../readline/readline.h"
# include "../readline/history.h"

# include "../libft/include/libft.h"
# include "colors.h"
# include "minishell_structs.h"

# include <fcntl.h>
# include <stdio.h>

/* MINISHELL */
void	print_minishell_welcome(char **env);
void	exit_minishell(t_shell *tshell);
void	start_signals(void);

char	*ft_readline(void);
void	split_intotokens(t_shell *tshell);
void	fill_token_location(t_shell *tshell);

/* PRINTING ERRORS */
void	print_err_args(void);
void	print_err_syntax(char *content);

/* TO TEST OR TESTING */
void	split_intocomands(t_shell *tshell);

/* MINISHELL STRUCTURE MEM MAN*/
void	free_tokens(t_shell *tshell);
void	*free_tshell(t_shell *tshell);
t_shell	*init_tshell(t_shell *tshell, char **env);

/* BUILTINS */
int		ft_echo(char *n, char *message);

/* UTILS FOR DEBBUG */
void	print_all_arrstr(char **arr);
void	print_tokens_st(t_list *tokens);
void	print_comands_st(t_list *cmd);

#endif
