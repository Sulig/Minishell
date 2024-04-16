/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/16 20:18:11 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fline(void)
{
	char	*ttp;

	ttp = "      echo       hello    \"$USER $$ $ $\"    look \"<|^_^|>\"";
	ttp = "echo hole > test1 > test2";
	ttp = "< file cat -e \"file\" ";
	ttp = "\"\"";
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
		print_tokens_st(tshell->tokens); //Print tokens list
		split_intocomands(tshell, tshell->tokens);
		tshell->line = ft_free_str(tshell->line);
		free_tokens(tshell);
		print_comands_st(tshell->comands);
		//Check if comand exist && execute
		if (tshell->cmd_size)
			redirect_and_execute(tshell);
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
