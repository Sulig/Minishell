/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:56:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/18 20:04:19 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../readline/readline.h"
# include "../readline/history.h"

# include "../libft/include/libft.h"
# include "colors.h"
# include "constants.h"
# include "minishell_structs.h"
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

/* STARTER THINGS */
void	print_minishell_welcome(char **env);
void	exit_minishell(t_shell *tshell);
void	start_signals(void);

/* CHECKERS */
int		check_valid_syntax(t_shell *tshell);
int		checkfor_unclosedquotes(t_shell *tshell, t_list *tokens);

/* MINISHELL */
char	*ft_readline(void);
void	split_intotokens(t_shell *tshell);
void	fill_token_location(t_shell *tshell);
void	expand_env_var(t_shell *tshell);
void	split_intocomands(t_shell *tshell, t_list *tokens);

/* TO TEST OR TESTING */
void	find_comands(t_shell *tshell, t_list *comands);
void	heredoc(t_shell *tshell, char *end, int fd);

/* REDIRECT AND EXECUTE */
void	redirect_and_execute(t_shell *tshell);

/* PRINTING ERRORS */
void	print_err_args(void);
int		print_err_syntax(char *content);
int		print_err_custom(char *error, int error_n);
int		print_comandnotfound(char *comand);

/* STRUCTURE MEMORY MANAGER */
void	free_tokens(t_shell *tshell);
void	free_comands(t_shell *tshell);
void	*free_tshell(t_shell *tshell);
t_shell	*init_tshell(t_shell *tshell, char **env);

/* UTILS */
int		is_builtin_name(t_cmd *cmd);
int		set_quote(char ch, int quoted);
void	set_path(t_shell *tshell);
t_cmd	*trim_input(t_cmd *cmd);
t_cmd	*asign_comandtype(t_cmd *cmd);
t_cmd	*quote_removal_comand(t_cmd *cmd);
t_list	*del_nullcomand(t_list *first, t_list *comand);
t_list	*polish_comands(t_list *first, t_list *comands);
/* UTILS FOR DEBBUG */
void	print_all_arrstr(char **arr);
void	print_tokens_st(t_list *tokens);
void	print_comands_st(t_list *cmd);

#endif
