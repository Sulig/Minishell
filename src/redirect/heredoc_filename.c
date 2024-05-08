/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:08:05 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/01 20:43:27 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Allocates and returns a string representing the here document temp filename
// for the 'n'-th command.
char	*heredoc_filename(int n)
{
	char	*tmp;
	char	*filename;

	filename = ft_strdup(HEREDOC_FILENAME_PREFIX);
	tmp = ft_itoa(n);
	ft_strjoin_free(&filename, tmp);
	free(tmp);
	return (filename);
}
