/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:44:15 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/02 08:51:41 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Removes the temporary here document 'file'.
void	clear_heredoc(const char *file)
{
	unlink(file);
}

// Removes the temporary here document files, up to the 'n'-th command.
void	clear_heredocs(int n)
{
	char	*filename;

	while (n-- >= 0)
	{
		filename = heredoc_filename(n);
		unlink(filename);
		free(filename);
	}
}
