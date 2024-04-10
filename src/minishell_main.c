/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/10 20:02:24 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fline(void)
{
	char	*ttp;

	ttp = "echo \"hello  $USER \" > file | grep h | cat << eof | cat >> file | echo 'done'";
	ttp = "<|°_°|>";
	return (ft_strdup(ttp));
}

void	minishell(t_shell *tshell)
{
	while (4)
	{
		tshell->line = ft_readline();
		//tshell->line = fline();
		if (!tshell->line)
			exit_minishell(tshell);
		split_intotokens(tshell);
		print_tokens_st(tshell->tokens);
		split_intocomands(tshell, tshell->tokens);
		tshell->line = ft_free_str(tshell->line);
		free_tokens(tshell);
		print_comands_st(tshell->comands);
		find_comands(tshell, tshell->comands);
		/* Redirections 
		 * Create file if don't exist
		 * If exist, read from it if we can, and save it in **tmp
		*/
		//redirect_and_execute(tshell);
		/* Executor
		 * Ejecute the comand
		 * if builtin, the output will be saved on a node of list
		 * 	** that node contains a fd
		 * 	** and the **args
		 *
		 * if comand, **unkownk
		*/
		free_comands(tshell);
		rl_on_new_line();
		break ;
	}
}

int	main(int argc, char **args, char **env)
{
	t_shell	*t_shell;
	int		exit_state;

	t_shell = NULL;
	if (argc != 1 || (ft_arr_strlen(args) > 2))
		print_err_args();
	print_minishell_welcome(env);
	t_shell = init_tshell(t_shell, env);
	start_signals();
	minishell(t_shell);
	exit_state = t_shell->exit_state;
	t_shell = free_tshell(t_shell);
	exit(exit_state);
	return (0);
}
