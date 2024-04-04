/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:49 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 19:02:18 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

static int	check_flag(char *word)
{
    if (word[0] == 'n' && ft_strlen(word) == 1)
        return (TRUE);
    else
	    return (FALSE);
}

// Output the 'args', separated by spaces, followed by a newline. 
// The return status is always 0. 
// If -n is specified, the trailing newline is suppressed.
int	builtin_echo(t_cmd *cmd)
{
	int	flag;
    
    flag = FALSE;
    if(cmd->options)
	    flag = check_flag(cmd->options);
    if(!flag && cmd->options)
    {
        printf("-%s",cmd->options);
        if (cmd->input)
            printf(" ");
    }
    if (cmd->input)
        printf("%s", cmd->input);
	if (flag == FALSE)
		printf("\n");
	return (0);
}