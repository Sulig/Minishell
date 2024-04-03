/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:47:46 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/03 16:41:36 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_comand(t_cmd *comand)
{
	char	*path;

	(void) comand
	path = getenv("PATH");
	if (!path)
		return (0);
	/*
	if (access(path, X_OK))
	drafw code, do not uncoment yet.
	*/
	return (1);
}
