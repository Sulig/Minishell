/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:57:31 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:29:24 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	arr_2d_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

char	**remove_last_elem_arr2d(char **arr)
{
	char	**new;
	int		len;
	int		i;

	i = 0;
	len = arr_2d_len(arr);
	new = (char **)malloc(sizeof(char *) * (arr_2d_len(arr)));
	if (!new)
		return (NULL);
	while (i < len - 1)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	free_arr_2d(arr);
	return (new);
}

char	**append_arr_2d(char **arr, char *s)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (arr_2d_len(arr) + 2));
	if (!new)
		return (NULL);
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = ft_strdup(s);
	i++;
	new[i] = NULL;
	free_arr_2d(arr);
	return (new);
}

/*
* Allocates and returns a copy of the NULL-terminated array of strings 'arr'
* with the 'i'th string removed from it. The original array 'arr' is freed.
* Exits properly if memory allocation fails.
*/
char	**remove_elem_arr2d(char **arr, int i)
{
	char	**orig_arr;
	char	**new_arr;
	int		orig_arr_size;
	int		j;

	orig_arr = arr;
	orig_arr_size = arr_2d_len(orig_arr);
	new_arr = (char **)malloc(sizeof(char *) * orig_arr_size);
	j = -1;
	while (++j < i)
		new_arr[j] = ft_strdup(orig_arr[j]);
	while (orig_arr[j + 1])
	{
		new_arr[j] = ft_strdup(orig_arr[j + 1]);
		++j;
	}
	new_arr[j] = NULL;
	free_arr_2d(arr);
	return (new_arr);
}
