/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:48:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/13 17:46:33 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include "minishell.h"

size_t	arr_size(const void **arr);
size_t	arrstr_size(char **arr);
char	**arrstr_dup(char **arr);
void	arrstr_free(char **arr);
char	**arrstr_add(char **arr, const char *str);
char	**arrstr_set(char **arr, const char *str, int i);

/* 2 */
void	*p_malloc(size_t size);
void	restore_exit(int exit_status);
void	ft_strjoin_free(char **s1, const char *s2);
void	free_ptr(void *ptr);
int		ft_strncmp_simple(const char *s1, const char *s2, size_t n);

#endif
