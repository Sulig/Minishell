/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/20 18:20:11 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*heredoc_filename(int n)
{
	char	*tmp;
	char	*filename;
	char	*path;

	filename = ft_strdup(HEREDOC_FILENAME_PREFIX);
	tmp = ft_itoa(n);
	path = ft_strjoin(filename, tmp);
	free(tmp);
	free(filename);
	return (path);
}
