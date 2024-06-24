/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:21:39 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/24 19:36:42 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../readline/readline.h"
# include "../readline/history.h"

# include "../libft/include/libft.h"
# include "boolean.h"
# include "colors.h"
# include "constants.h"
# include "minishell_structs.h"
# include "builtins.h"
# include "exec.h"
# include "env.h"
# include "arr_2d.h"
# include "libft_utils.h"
# include "redirect.h"
# include "signals.h"
# include "heredoc.h"
# include "limits.h"
# include "errors.h"

# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

/* CHECKERS */
int		check_valid_syntax(t_shell *tshell);
int		checkfor_unclosedquotes(t_shell *tshell, t_list *tokens);
int		check_beforecreate(t_shell *tshell, t_token *token);

/* MINISHELL */
char	*ft_readline(void);
void	exit_minishell(t_shell *tshell);
void	heredoc(t_shell *tshell, char *end, int fd);
void	split_intotokens(t_shell *tshell);

/* Testing */
void	split_intocomands(t_shell *tshell, t_list *tokens);
t_cmd	*fill_comand_flags(t_cmd *cmd, t_list *tokens, size_t *pos);
//t_cmd	*fill_comand_input(t_cmd *cmd, t_list *tokens, size_t *pos);
//t_cmd	*fill_comand_args(t_cmd *cmd);

t_token	**push_intoarr(t_token **original, t_token *add);

/* REDIRECT AND EXECUTE */
void	redirect_and_execute(t_shell *tshell);

/* PRINTING ERRORS */
void	print_err_args(void);
int		print_err_syntax(char *content);
int		print_err_custom(char *error, int error_n);
int		print_comandnotfound(char *comand);
int		print_comun_error(char *error, int error_n);

/* STRUCTURE MEMORY MANAGER */
t_list	*free_tokens_list(t_list **tokens);
void	free_tokens(t_shell *tshell);
void	free_comands(t_shell *tshell);
void	free_tree_cmds(t_shell *tshell);
void	*free_tshell(t_shell *tshell);
t_shell	*init_tshell(t_shell *tshell, char **env);

/* UTILS */
t_list	*split_intotokens_forexpand(char *line);
t_list	*free_tokens_list(t_list **tokens);
t_list	*fill_token_location(t_list *tokens);
t_list	*splitline_intotokens(char *line);

int		is_builtin_name(t_cmd *cmd);
int		set_quote(char ch, int quoted);
void	set_path(t_shell *tshell);
t_cmd	*asign_comandtype(t_cmd *cmd);
char	*expand_heredoc_vars(char *str, char **env, int exit);

/* UTILS FOR DEBBUG */
void	print_all_arrstr(char **arr);
void	print_tokens_st(t_list *tokens);
void	print_comands_st(t_list *cmd);
void	print_multiple_cmds_st(t_list **cmds);

#endif
