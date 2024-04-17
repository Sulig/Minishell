/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:25:51 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:50 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	return new pwd path
*/
char	*concat_path(char **env, char *str)
{
	char	*s;
	char	*temp;
	int		i;

	i = 0;
	s = ft_strdup(str);
	temp = ft_strdup(s);
	free(s);
	while (env[i])
	{
		s = ft_strjoin_s(temp, "/");
		free(temp);
		temp = ft_strdup(s);
		free(s);
		s = ft_strjoin_s(temp, env[i]);
		free(temp);
		temp = ft_strdup(s);
		free(s);
		i++;
	}
	s = ft_strdup(temp);
	free(temp);
	return (s);
}
