/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_pathwithargs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:26:38 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/09 17:13:47 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**free_case(char **tofree, int free, int strcase)
{
	if (free == strcase)
	{
		tofree = ft_auto_free_arr(tofree);
		return (NULL);
	}
	else if (free == 3)
	{
		tofree = ft_auto_free_arr(tofree);
		return (NULL);
	}
	else
		return (tofree);
}

/*
* Creates a new array with the result of joining two arrays
* * If free = 0 -> do not free
* * If free = 1 -> free arr1
* * If free = 2 -> free arr2
* * If free = 3 -> free arr1 & arr2
*/
char	**join_strarr(char **arr1, char **arr2, int free)
{
	char	**result;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_arr_strlen(arr1) + ft_arr_strlen(arr2);
	result = ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (arr1)
		while (arr1[j])
			result[i++] = ft_strdup(arr1[j++]);
	j = 0;
	if (arr2)
		while (arr2[j])
			result[i++] = ft_strdup(arr2[j++]);
	arr1 = free_case(arr1, free, 1);
	arr2 = free_case(arr2, free, 2);
	return (result);
}

char	**joinpath_withargs(char *path, char **flags, char **args)
{
	char	**result;
	char	**tmp;
	size_t	size;

	size = ft_arr_strlen(flags) + ft_arr_strlen(args) + 1;
	result = ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(path);
	tmp = join_strarr(flags, args, 0);
	if (!tmp)
		return (result);
	result = join_strarr(result, tmp, 3);
	return (result);
}
