/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/22 19:08:20 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fline(size_t _case)
{
	static size_t	bruh;
	char			*ttp;

	if (_case)
		bruh = _case;
	if (!bruh)
		ttp = "      echo       hello    \"$USER $$ $ $\"    look \"<|^_^|>\"";
	else if (bruh == 1)
		ttp = "echo hole > test1 > test2";
	else if (bruh == 2)
		ttp = "< file cat -e \"file\" ";
	else if (bruh == 3)
		ttp = "<|°_°|>";
	else if (bruh == 4)
		ttp = "export HELLO=122";
	else if (bruh == 5)
		ttp = "< file cat -e";
	else if (bruh == 6)
		ttp = "comand name\" -option ";
	else if (bruh == 7)
		ttp = "echo > fgh | < file cat -e";
	else if (bruh == 8)
		ttp = "cat Makefile > gig | > h | >> a | cat h > >";
	else if (bruh == 9)
		ttp = "ls -l -a -b arhchive | leaks -atExit -- ./minishell";
	else if (bruh == 10)
		ttp = "cd $pwd\\src";
	else if (bruh == 11)
		ttp = "echo \'exit_code ->$? user ->$USER home -> $HOME\'";
	else if (bruh == 12)
		ttp = "echo $?HELLO > tgh >";
	else
		ttp = "";
	bruh++;
	return (ft_strdup(ttp));
}

static int	control_and_c(int exit_status)
{
	if (g_signal == SIGINT)
		exit_status = EXIT_FAILURE;
	signal(SIGINT, SIG_IGN);
	return (exit_status);
}

void	test_heredoc(char *file, t_shell *tshell)
{
	int		fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
		ft_printf_fd(2, "Incorrect file");
	else
		heredoc(tshell, "EOF" , fd);
	close(fd);
}

void	minishell(t_shell *tshell)
{
	while (4)
	{
		set_signals(INTER);
		tshell->line = ft_readline();
		//tshell->line = fline(0);
		tshell->exit_state = control_and_c(tshell->exit_state);
		if (!tshell->line)
			exit_minishell(tshell);
		split_intotokens(tshell);
		//print_tokens_st(tshell->tokens); //Print tokens list
		split_intocomands(tshell, tshell->tokens);
		//print_comands_st(tshell->comands); //Print cmd list
		tshell->line = ft_free_str(tshell->line);
		split_intodoublelist(tshell);
		//print_multiple_cmds_st(tshell->tree_cmd); //Print tree_cmd
		free_tokens(tshell);
		//test_heredoc("test.txt", tshell); //test heredoc
		create_cmd_from_cmd(tshell);
		if (tshell->cmd_size && tshell->tree_cmd)
			redirect_and_execute(tshell);
		free_comands(tshell);
		free_tree_cmds(tshell);
		rl_on_new_line();
		//break ;
	}
}

int	main(int argc, char **args, char **env)
{
	t_shell	*t_shell;
	int		exit_state;

	t_shell = NULL;
	if (argc != 1 || (ft_arr_strlen(args) > 2))
		print_err_args();
	//print_minishell_welcome(env);
	t_shell = init_tshell(t_shell, env);
	if (!t_shell)
		return (print_err_custom(MERR_MALLOC, 1));
	minishell(t_shell);
	exit_state = t_shell->exit_state;
	t_shell = free_tshell(t_shell);
	exit(exit_state);
	return (0);
}
