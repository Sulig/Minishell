/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:49:39 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:19:28 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Restores the default print signal config and exits returning 'exit_status'.
void	restore_exit(int exit_status)
{
	signals_print_handler(TRUE);
	exit(exit_status);
}

// Allocates 'size' bytes of memory and returns a pointer to it.
// Exits properly if memory allocation fails.
void	*p_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		restore_exit(EXIT_FAILURE);
	return (ptr);
}

// Sets the value of the 'i'th string in the NULL-terminated array of strings
// 'arr' to the string 'str'. Returns 'arr'.
// Pre: 'i' must be smaller than the 'arr' size.
char	**arrstr_set(char **arr, const char *str, int i)
{
	free(arr[i]);
	arr[i] = ft_strdup(str);
	return (arr);
}
