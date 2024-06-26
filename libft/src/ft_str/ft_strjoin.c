/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:11:30 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 19:57:46 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lenght.h"

/*
 * Join the s1 & s2
 * Probaly segfault when !s1 || !s2
 * Use ft_strjoin_s instead 
 * Return char * joined
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	int		cnt;
	char	*join;

	join = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	len = 0;
	cnt = 0;
	while (s1[cnt])
		join[len++] = s1[cnt++];
	cnt = 0;
	while (s2[cnt])
		join[len++] = s2[cnt++];
	join[len] = '\0';
	return (join);
}

/*
 * Join the s1 & s2
 * + Protection on case !s1 || !s2
 * Return char * joined
 */
char	*ft_strjoin_s(const char *s1, const char *s2)
{
	int		len;
	int		cnt;
	char	*join;

	join = malloc((ft_strllen(s1) + ft_strllen(s2)) + 1);
	if (!join)
		return (NULL);
	len = 0;
	cnt = 0;
	if (s1)
		while (s1[cnt])
			join[len++] = s1[cnt++];
	cnt = 0;
	if (s2)
		while (s2[cnt])
			join[len++] = s2[cnt++];
	join[len] = '\0';
	return (join);
}

/*
 * Join the s1 & s2
 * + Protection on case !s1 || !s2
 * Free the s1 before returning the join
 * Return char * joined
*/
char	*ft_strjoin_free_fst(char *s1, const char *s2)
{
	int		len;
	int		cnt;
	char	*join;

	join = malloc((ft_strllen(s1) + ft_strllen(s2)) + 1);
	if (!join)
		return (NULL);
	len = 0;
	cnt = 0;
	if (s1)
		while (s1[cnt])
			join[len++] = s1[cnt++];
	cnt = 0;
	if (s2)
		while (s2[cnt])
			join[len++] = s2[cnt++];
	join[len] = '\0';
	if (s1)
		free(s1);
	s1 = NULL;
	return (join);
}

/*
 * Join the s1 & s2
 * + Protection on case !s1 || !s2
 * Free the s2 before returning the join
 * Return char * joined
*/
char	*ft_strjoin_free_sec(const char *s1, char *s2)
{
	int		len;
	int		cnt;
	char	*join;

	join = malloc((ft_strllen(s1) + ft_strllen(s2)) + 1);
	if (!join)
		return (NULL);
	len = 0;
	cnt = 0;
	if (s1)
		while (s1[cnt])
			join[len++] = s1[cnt++];
	cnt = 0;
	if (s2)
		while (s2[cnt])
			join[len++] = s2[cnt++];
	join[len] = '\0';
	if (s2)
		free(s2);
	s2 = NULL;
	return (join);
}
