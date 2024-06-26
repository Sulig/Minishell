/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:07:49 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/19 18:54:55 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lenght.h"
#include "../include/memory.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	len = 0;
	if (!ft_strllen(s1))
		return (NULL);
	while (s1[len])
		len++;
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		cpy[len] = s1[len];
		len++;
	}
	cpy[len] = '\0';
	return (cpy);
}

char	*ft_strremplace(char *dst, const char *str)
{
	dst = ft_free_str(dst);
	if (!ft_strllen(str))
		return (NULL);
	dst = ft_strdup(str);
	return (dst);
}

char	*ft_strcpyl(const char *s1, size_t len)
{
	char	*cpy;
	size_t	cnt;

	if (!s1 || len <= 0)
		return (NULL);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	cnt = 0;
	while (cnt < len)
	{
		cpy[cnt] = s1[cnt];
		cnt++;
	}
	cpy[len] = '\0';
	return (cpy);
}

char	**ft_strarrdup(char **to_copy)
{
	char	**copy;
	size_t	cnt;

	cnt = 0;
	copy = ft_calloc(sizeof(char *), ft_arr_strlen(to_copy) + 1);
	if (!copy)
		return (NULL);
	if (to_copy)
	{
		while (to_copy[cnt])
		{
			copy[cnt] = ft_strdup(to_copy[cnt]);
			cnt++;
		}
	}
	return (copy);
}
