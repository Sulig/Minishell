/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/12 19:41:26 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_shell *tshell)
{
	while (4)
	{
		start_signals();
		tshell->line = ft_readline();
		if (!tshell->line)
			exit_minishell(tshell);
		tshell = split_intotokens(tshell);
		tshell->line = ft_free_str(tshell->line);
		print_tokens_st(tshell->tokens);
		ft_printf("Comands encountered: %i\n", comand_counter(tshell->tokens));
		//parser \\> error handler case ...
		free_tokens(tshell);
		//expand, split (echo " case "), quote removal
		//Redirect \\> error on filedescriptors
		//execute \\> error execution
		//exit status or contiue in loop
		rl_on_new_line();
		break ;
	}
}

int	main(int argc, char **args, char **env)
{
	t_shell	*t_shell;

	t_shell = NULL;
	if (argc != 1 || (ft_arr_strlen(args) > 2))
		print_err_args();
	print_minishell_welcome(env);
	t_shell = init_tshell(t_shell, env);
	minishell(t_shell);
	t_shell = free_tshell(t_shell);
	return (0);
}
