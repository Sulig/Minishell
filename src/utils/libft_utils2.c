/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:49:39 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:30:53 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_exit(int exit_status)
{
	while (exit_status < 0)
		exit_status = 256 + exit_status;
	signals_print_handler(TRUE);
	exit(exit_status);
}

void	*p_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		restore_exit(EXIT_FAILURE);
	return (ptr);
}

char	**arrstr_set(char **arr, const char *str, int i)
{
	free(arr[i]);
	arr[i] = ft_strdup(str);
	return (arr);
}

/* free_ptr:
*	Frees a pointer of any type if it is not NULL and sets it to NULL.
*	This avoids accidental double-frees.
*/
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

/*
	DESCRIPTION :
	The function ft_strncmp compares the first n bytes of the given strings
	s1 and s2.

	RETURN VALUE :
	An integer less than, equal to, or greater than zero if one of the first
	n bytes of s1 is found to be less than, to match, or to be greater than
	s2.
*/
int	ft_strncmp_simple(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' && s2[i] != '\0')
		&& (i < n - 1) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
