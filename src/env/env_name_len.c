/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:53 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 22:31:02 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Given that 'str' points to the first character of a variable name,
// returns its length.
int	env_name_len(const char *str)
{
	int	i;

	i = 0;
	if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		++i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			++i;
	}
	return (i);
}