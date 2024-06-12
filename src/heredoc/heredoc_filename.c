/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:20 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/12 19:27:35 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
