/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:50:44 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/15 16:14:20 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int check_if_pipe(t_list *cmds)
{
    t_cmd   *cmd;

    while (cmds)
    {
        cmd = cmds->content;
        if (cmd->cmdtype == PIPE)     
            return (TRUE);       
        cmds = cmds->next;
    }
    return (FALSE);
}

/*
 * Redirects and executes the given command 'cmd' 
 * on the current shell environment, returning the exit status.
*/
static int	process_builtin_here(t_list *cmds, t_shell *tshell)
{
	int		exit_status;
    t_list	*lst;
	t_cmd	*first;

    lst = cmds;
	save_restore_stdio(tshell, STDIN_FILENO, STDOUT_FILENO, SAVE);
	exit_status = 0;
	//read_heredocs(cmd, 0, tshell->env);
	if (exit_status)
		return (exit_status);
	exit_status = redirect(cmds);
	if (exit_status != 0)
	{
		save_restore_stdio(tshell, STDIN_FILENO, STDOUT_FILENO, RESTORE);
		return (exit_status);
	}
	first = (t_cmd *)cmds->content;
	if (ft_lstsize(cmds) > 0)
		exit_status = execute_builtin(first, tshell->exit_state, tshell->env);
	save_restore_stdio(tshell, STDIN_FILENO, STDOUT_FILENO, RESTORE);
	return (exit_status);
}

/*
 * Iterate throught commands and check if that command is a builtin command
 * If there is only one command execute_simple_cmd
*/
void	redirect_and_execute(t_shell *tshell)
{
    t_list	*cmds;
    int		exit_status;

	if (!tshell->comands)
		return ;
    cmds = tshell->comands;
	exit_status = tshell->exit_state;
    if (check_if_pipe(cmds) == FALSE)
    {
        if (ft_lstsize(cmds) == 1)
            exit_status = execute_simple_cmd(cmds->content, tshell->env);
        else
            exit_status = process_builtin_here(cmds, tshell);
    }
    else
    {
        //HAY QUE SEPARAR LA LISTA DE COMANDOS
    }
    tshell->exit_state = exit_status;

    
    //si el primer comando es builting -> miramos si el siguiente existe y es redir o pipe.
    //Si no hay nada, ejecutamos builting
    //Si hay redir, antes ejecutamos redireccionamiento y despues builting
    //Si hay pipe, redireccionamos la salida del comando a la entrada del comando que haya despues del pipe
}
