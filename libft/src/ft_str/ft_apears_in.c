/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apears_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:57:29 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/07 17:17:56 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_apears_ch_in_str(char *str, char ch)
{
	size_t	len;
	size_t	times_ap;

	len = 0;
	times_ap = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		if (str[len] == ch)
			times_ap++;
		len++;
	}
	if (!times_ap && !str[len])
		return (1);
	return (times_ap);
}

size_t	ft_apears_str_in_str(const char *haystack, const char *needle)
{
	size_t	cnt;
	size_t	cntn;
	size_t	times_ap;

	if (!haystack || !needle)
		return (0);
	cnt = 0;
	times_ap = 0;
	while (haystack[cnt] != '\0')
	{
		cntn = 0;
		while (haystack[cnt] == needle[cntn] && haystack[cnt])
		{
			++cnt;
			++cntn;
		}
		if (needle[cntn] == '\0')
			times_ap++;
		cnt = cnt - cntn + 1;
	}
	return (times_ap);
}
