/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:50:44 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/10 18:32:25 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

/*
** Iterate throught commands and check if that command is a builtin command
** If there is only one command execute_simple_cmd
*/
void    redirect_and_execute(t_shell *tshell)
{
    t_list  *cmds;
    int     exit_status;

	if (tshell->exit_state != 0)
		return ;
    cmds = tshell->comands;
    if(ft_lstsize(cmds) == 1)
    {
        exit_status = execute_simple_cmd(cmds->content, tshell->env);
    }
    
    
    //si el primer comando es builting -> miramos si el siguiente existe y es redir o pipe.
    //Si no hay nada, ejecutamos builting
    //Si hay redir, antes ejecutamos redireccionamiento y despues builting
    //Si hay pipe, redireccionamos la salida del comando a la entrada del comando que haya despues del pipe
    
}
