/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:46:41 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/24 16:49:13 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Returns the size of the given NULL-terminated array 'arr'.
size_t	arr_size(const void **arr)
{
	size_t	size;

	size = 0;
	while (arr && arr[size])
		++size;
	return (size);
}

// Counts and returns the amount of elements in the NULL-terminated array 'arr'.
size_t	arrstr_size(char **arr)
{
	return (arr_size((void *)arr));
}

// Allocates and returns a copy of the NULL-terminated array of strings 'arr'.
// Exits properly if memory allocation fails.
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

// Frees the NULL-terminated array of strings 'arr'.
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
