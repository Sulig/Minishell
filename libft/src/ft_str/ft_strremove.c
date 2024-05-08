/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:17:11 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/08 19:57:43 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/lenght.h"
#include "../include/searchers.h"
#include "../include/string_utils.h"
#include "../include/memory.h"

char	*ft_strremove(char *str, const char *rem)
{
	char	*result;
	char	*start;
	char	*end;
	size_t	pos;

	if (!str)
		return (NULL);
	if (!rem || !ft_strstr(str, rem))
		return (str);
	if (my_strcmp(str, rem))
	{
		str = ft_free_str(str);
		return (NULL);
	}
	pos = ft_cnt_tostr(str, rem);
	start = ft_substr(str, 0, pos);
	end = ft_substr(str, pos + ft_strllen(rem) - 1, ft_strllen(str));
	result = ft_strjoin_s(start, end);
	start = ft_free_str(start);
	end = ft_free_str(end);
	str = ft_free_str(str);
	if (!ft_strstr(result, rem))
		return (result);
	return (ft_strremove(result, rem));
}
