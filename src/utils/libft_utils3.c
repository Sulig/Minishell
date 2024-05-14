/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:49:39 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/14 17:15:42 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
long long	ft_atoll(char *str)
{
	long long	res;
	char		sign;
	int			i;

	res = 0;
	sign = '+';
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i];
		i++;
	}
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (long long)str[i] - '0';
		i++;
		if (res == LONG_MAX / 10 && str[i] == '8')
			return (LONG_MIN);
	}
	if (sign == '-')
		return (-res);
	return (res);
}
