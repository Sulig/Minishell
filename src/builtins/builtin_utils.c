/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:24:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 17:50:55 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Returns TRUE if the string 'str' is the name of a builtin.
int	is_builtin_name(const char *str)
{
	if (!ft_strncmp(str, "cd", 3) || !ft_strncmp(str, "echo", 5) || \
	!ft_strncmp(str, "env", 4) || !ft_strncmp(str, "exit", 5) || \
	!ft_strncmp(str, "export", 7) || !ft_strncmp(str, "pwd", 4) || \
	!ft_strncmp(str, "unset", 6))
		return (TRUE);
	return (FALSE);
}