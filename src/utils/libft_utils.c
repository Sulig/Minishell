/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:46:41 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:30:41 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	arr_size(const void **arr)
{
	size_t	size;

	size = 0;
	while (arr && arr[size])
		++size;
	return (size);
}

size_t	arrstr_size(char **arr)
{
	return (arr_size((void *)arr));
}

char	**arrstr_dup(char **arr)
{
	char	**new_arr;
	int		orig_arr_size;
	int		i;

	orig_arr_size = arrstr_size(arr);
	new_arr = (char **)p_malloc(sizeof(char *) * (orig_arr_size + 1));
	i = -1;
	while (++i < orig_arr_size)
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}

void	arrstr_free(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(arr);
}

char	**arrstr_add(char **arr, const char *str)
{
	char	**new_arr;
	int		orig_arr_size;
	int		i;

	orig_arr_size = arrstr_size(arr);
	new_arr = (char **)p_malloc(sizeof(char *) * (orig_arr_size + 2));
	i = -1;
	while (++i < orig_arr_size)
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	arrstr_free(arr);
	return (new_arr);
}
