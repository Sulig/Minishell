/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:17:11 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/20 09:45:38 by jguillot         ###   ########.fr       */
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
	end = str + pos + ft_strllen(rem);
	result = ft_strjoin_s(start, end);
	start = ft_free_str(start);
	end = NULL;
	str = ft_free_str(str);
	if (!ft_strstr(result, rem))
		return (result);
	return (ft_strremove(result, rem));
}
