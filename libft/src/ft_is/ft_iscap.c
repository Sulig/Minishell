/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:05:41 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/10 19:06:01 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_cap(char c)
{
	if (c > '/' && c < ':')
		return (1);
	if (c > '@' && c < '[')
		return (1);
	return (0);
}
