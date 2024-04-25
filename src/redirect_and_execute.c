/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:00:07 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 17:13:46 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

// Redirects and executes the command 'cmd' in a subshell, taking into account
// it is the i-th command of the pipeline.
// It exits with the appropriate exit status, or returns with a non-zero value.
static int	process_command(t_pipe *p, t_list *cmds, int e_stat, char **env)
{
	int		exit_stat;

	if (p->i > 0)
		link_read_end(p->prev_fds);
	if (p->i < p->cmds_amount - 1)
		link_write_end(p->next_fds);
	exit_stat = redirect(cmds);
	if (exit_stat != 0)
		exit(exit_stat);
	if (ft_lstsize(cmds) == 0)
		exit(EXIT_SUCCESS);
	execute_command(cmds, e_stat, env);
	return (EXIT_FAILURE);
}

// Updates the pipe's file descriptor updates from the parent process for the
// i-th command, closing previous file descriptors and preparing for next.
static void	parent_pipe_update(t_pipe *p, int i)
{
	if (i > 0)
	{
		close(p->prev_fds[READ_END]);
		close(p->prev_fds[WRITE_END]);
	}
	if (i < p->cmds_amount - 1)
	{
		p->prev_fds[READ_END] = p->next_fds[READ_END];
		p->prev_fds[WRITE_END] = p->next_fds[WRITE_END];
	}
}

// Redirects and executes the commands defined by the array of commands 'cmds',
// assuming p->cmds_amount is already initialized. All commands are executed in
// subprocesses. Returns the exit status of the last command.
static int	process_commands(t_list **piped_cmds, t_pipe *p, int e_stat, char **env)
{
	int		exit_stat;
	int		i;
	pid_t	pid;
	pid_t	last_child;

	last_child = 0;
	exit_stat = 0;// read_all_heredocs(piped_cmds, p->cmds_amount, env);
	if (exit_stat)
		return (exit_stat);
	stop_signals();
	i = -1;
	while (++i < p->cmds_amount)
	{
		p->i = i;
		if (i < p->cmds_amount - 1)
			pipe_or_die(p->next_fds);
		pid = fork_or_die();
		//if (pid == 0)
			return (process_command(p, piped_cmds[i], e_stat, env));
		parent_pipe_update(p, i);
		last_child = pid;
	}
	exit_stat = wait_children(last_child, p->cmds_amount);
	//clear_heredocs(p->cmds_amount);
	return (exit_stat);
}

// Redirects and executes the given command 'cmd' on the current shell
// environment, returning the exit status.
static int	process_builtin_here(t_list *piped_cmds, int exit_status, char **env)
{
	int	exit_stat;

	save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, SAVE);
	exit_stat = 0;//read_heredocs(*cmd, 0, *env);
	if (exit_stat)
		return (exit_stat);
	exit_stat = redirect(piped_cmds);
	if (exit_stat != 0)
	{
		save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, RESTORE);
		return (exit_stat);
	}
	if (ft_lstsize(piped_cmds) > 0)
		exit_stat = execute_builtin(piped_cmds, exit_status, env, FALSE);
	save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, RESTORE);
	return (exit_stat);
}

// Performs all redirections and command/builtin executions defined by the array
// of lists 'commands', updating the 'exit_status' and environment 'env'
// accordingly.
void	redirect_and_execute(t_list **piped_cmds, int *exit_status, char **env)
{
	t_pipe	p;

	p.cmds_amount = arr_size((void *)piped_cmds);
	if (p.cmds_amount == 0)
		*exit_status = 0;
	else if (p.cmds_amount == 1 && is_builtin_cmd(piped_cmds[0]))
		*exit_status = process_builtin_here(piped_cmds[0], *exit_status, env);
	else
		*exit_status = process_commands(piped_cmds, &p, *exit_status, env);
}
