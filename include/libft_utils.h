/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:48:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/21 16:25:04 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include "minishell.h"

size_t		arr_size(const void **arr);
size_t		arrstr_size(char **arr);
char		**arrstr_dup(char **arr);
void		arrstr_free(char **arr);
char		**arrstr_add(char **arr, const char *str);
char		**arrstr_set(char **arr, const char *str, int i);

/* 2 */
void		*p_malloc(size_t size);
void		restore_exit(int exit_status);
void		ft_strjoin_free(char **s1, const char *s2);
void		free_ptr(void *ptr);
int			ft_strncmp_simple(const char *s1, const char *s2, size_t n);

/* 3 */
long long	ft_atoll(char *str);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);

/* token_utils */
int			count_tokens(t_token **toks);
char		*get_name_from_cmd(t_cmd *comand);
char		**get_arr_input_from_cmd(t_cmd *comand);
char		**get_arr_flags_from_cmd(t_cmd *comand);
int			check_comand(t_shell *tshell);
void		prepare_echo(t_list *piped_cmd);

#endif
