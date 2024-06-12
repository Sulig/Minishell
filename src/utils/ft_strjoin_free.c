/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:24:21 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:30:18 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	p_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static size_t	p_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = p_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (src && src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

static size_t	p_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	dlen;
	size_t	n;

	n = dstsize;
	dst_cpy = dst;
	src_cpy = (char *)src;
	while (n-- != 0 && *dst)
		dst++;
	dlen = dst - dst_cpy;
	n = dstsize - dlen;
	if (n == 0)
		return (dlen + p_strlen(src));
	while (*src)
	{
		if (n != 1)
		{
			*dst++ = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';
	return (dlen + (src - src_cpy));
}

void	ft_strjoin_free(char **s1, const char *s2)
{
	size_t	strsize;
	char	*str;

	strsize = p_strlen(*s1) + p_strlen(s2) + 1;
	str = (char *)p_malloc(strsize * sizeof(char));
	p_strlcpy(str, *s1, strsize);
	p_strlcat(str, s2, strsize);
	free(*s1);
	*s1 = str;
}
