/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:50 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/08 18:11:49 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fline(void)
{
	return (" echo \"Alastor    loves you ~ $USER\" > test.txt | cat text.txt\0");
}

void	minishell(t_shell *tshell)
{
	while (4)
	{
		start_signals();
		tshell->line = fline();
		//tshell->line = ft_readline();
		if (!tshell->line)
			exit_minishell(tshell);
		//tokenize \\> error handler case " ' 
		tshell = split_intotokens(tshell);
		//tshell->line = ft_free_str(tshell->line);
		//parser \\> error handler case ...
		//expand, split (echo " case "), quote removal
		//Redirect \\> error on filedescriptors
		//execute \\> error execution
		//exit status or contiue in loop
		rl_on_new_line();
		free_tokens(tshell);
		//ft_lstclear(&tshell->tokens, free);
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
