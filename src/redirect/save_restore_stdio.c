/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_restore_stdio.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:01:56 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 14:14:54 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// If 'mode' = SAVE: Saves the standard input and output.
// If 'mode' = RESTORE: Restores the previously saved standard input and output.
void	save_restore_stdio(int std_in, int std_out, int mode)
{
	static int	saved_stdin;
	static int	saved_stdout;

	if (mode == SAVE)
	{
		saved_stdin = dup(std_in);
		saved_stdout = dup(std_out);
	}
	if (mode == RESTORE)
	{
		dup2(saved_stdin, std_in);
		close(saved_stdin);
		dup2(saved_stdout, std_out);
		close(saved_stdout);
	}
}
