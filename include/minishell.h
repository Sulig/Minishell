/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:56:43 by sadoming          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/19 19:34:48 by sadoming         ###   ########.fr       */
=======
/*   Updated: 2024/03/30 09:17:02 by jguillot         ###   ########.fr       */
>>>>>>> Add files via upload
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/include/libft.h"
# include "colors.h"
# include "constants.h"
# include "minishell_structs.h"
<<<<<<< HEAD
# include "exec.h"
# include "boolean.h"
# include "builtins.h"
# include "env.h"
# include "arr_2d.h"
# include "redirect.h"

# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
=======
# include "redirections.h"
# include "boolean.h"
# include "lst.h"
# include "builtin.h"
# include "env.h"

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
>>>>>>> Add files via upload


/* MINISHELL */
void	print_minishell_welcome(char **env);
void	exit_minishell(t_shell *tshell);
void	start_signals(void);

<<<<<<< HEAD
/* CHECKERS */
int		check_valid_syntax(t_shell *tshell);
int		checkfor_unclosedquotes(t_shell *tshell, t_list *tokens);

/* MINISHELL */
=======
>>>>>>> Add files via upload
char	*ft_readline(void);
void	split_intotokens(t_shell *tshell);
void	fill_token_location(t_shell *tshell);
void	expand_env_var(t_shell *tshell);
<<<<<<< HEAD
void	split_intocomands(t_shell *tshell, t_list *tokens);

/* TO TEST OR TESTING */
t_cmd	*quote_removal(t_shell *tshell, t_cmd *cmd);
void	heredoc(t_shell *tshell, char *end, int fd);

/* REDIRECT AND EXECUTE */
void	redirect_and_execute(t_shell *tshell);

/* PRINTING ERRORS */
void	print_err_args(void);
int		print_err_syntax(char *content);
int		print_err_custom(char *error, int error_n);
int		print_comandnotfound(char *comand);

/* STRUCTURE MEMORY MANAGER */
=======

/* PRINTING ERRORS */
void	print_err_args(void);
int 	print_err_syntax(char *content);
int     print_err_numeric_arg(const char *content);

/* TO TEST OR TESTING */
void	split_intocomands(t_shell *tshell, t_list *tokens);
int     count_elements(char **array);

/* CHECKERS */
int		check_valid_syntax(t_shell *tshell);
int		checkfor_unclosedquotes(t_shell *tshell, t_list *tokens);

/* MINISHELL STRUCTURE MEM MAN*/
>>>>>>> Add files via upload
void	free_tokens(t_shell *tshell);
void	free_comands(t_shell *tshell);
void	*free_tshell(t_shell *tshell);
void	free_comands(t_shell *tshell);
t_shell	*init_tshell(t_shell *tshell, char **env);

/* UTILS */
int		is_builtin_name(t_cmd *cmd);
int		set_quote(char ch, int quoted);
void	set_path(t_shell *tshell);
t_cmd	*trim_input(t_cmd *cmd);
t_cmd	*asign_comandtype(t_cmd *cmd);
t_list	*del_nullcomand(t_list *first, t_list *comand);
t_list	*polish_comands(t_shell *tshell, t_list *first, t_list *comands);
/* UTILS FOR DEBBUG */
void	print_all_arrstr(char **arr);
void	print_tokens_st(t_list *tokens);
void	print_comands_st(t_list *cmd);

/* UTILS */
void	ft_strjoin_free(char **s1, const char *s2);
t_cmd	*asign_comandtype(t_cmd *cmd);
void	restore_exit(int exit_status);

#endif
