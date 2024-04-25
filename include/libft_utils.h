/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:48:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 13:33:29 by jguillot         ###   ########.fr       */
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

#endif
