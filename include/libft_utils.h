/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:48:18 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 16:52:17 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

size_t	arr_size(const void **arr);
size_t	arrstr_size(char **arr);
char	**arrstr_dup(char **arr);
void	arrstr_free(char **arr);
/* 2 */
void	*p_malloc(size_t size);
void	restore_exit(int exit_status);

#endif
