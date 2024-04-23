/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/23 17:47:41 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fline(void)
{
	static int	bruh;
	char		*ttp;

	bruh = 9;
	if (!bruh)
		ttp = "      echo       hello    \"$USER $$ $ $\"    look \"<|^_^|>\"";
	else if (bruh == 1)
		ttp = "echo hole > test1 > test2";
	else if (bruh == 2)
		ttp = "< file cat -e \"file\" ";
	else if (bruh == 3)
		ttp = "<|°_°|>";
	else if (bruh == 4)
		ttp = "cat|ls bruh";
	else if (bruh == 5)
		ttp = "< file cat -e";
	else if (bruh == 6)
		ttp = "comand name\" -option ";
	else if (bruh == 7)
		ttp = "\"i will don't close";
	else if (bruh == 8)
		ttp = "sometext \"i will don't close";
	else if (bruh == 9)
		ttp = "echo -  heloo";
	else 
		ttp = NULL;
	bruh++;
	return (ft_strdup(ttp));
}

void	minishell(t_shell *tshell)
{
	while (4)
	{
		//tshell->line = ft_readline();
		tshell->line = fline();
		if (!tshell->line)
			exit_minishell(tshell);
		split_intotokens(tshell);
		print_tokens_st(tshell->tokens); //Print tokens list
		split_intocomands(tshell, tshell->tokens);
		tshell->line = ft_free_str(tshell->line);
		free_tokens(tshell);
		print_comands_st(tshell->comands);
		//Check if comand exist && execute
		//if (tshell->cmd_size)
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
	if (!t_shell)
		return (print_err_custom(MERR_MALLOC, 1));
	start_signals();
	minishell(t_shell);
	exit_state = t_shell->exit_state;
	t_shell = free_tshell(t_shell);
	exit(exit_state);
	return (0);
}
