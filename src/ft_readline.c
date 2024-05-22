/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:45:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/22 19:06:59 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_shell *tshell)
{
	int	exit_state;

	exit_state = tshell->exit_state;
	rl_clear_history();
	tshell = free_tshell(tshell);
	ft_printf_fd(2, "minishell$: exit\n");
	exit(exit_state);
}

char	*ft_readline(void)
{
	char	*line;

	line = readline(PROMPT);
	if (ft_strllen(line))
		add_history(line);
	return (line);
}

void	heredoc(t_shell *tshell, char *end, int fd)
{
	char	*tmp;
	char	*joined;

	joined = NULL;
	while (4)
	{
		tmp = readline(HEREDOC);
		if (!tmp)
			break ;
		if (my_strcmp(end, tmp))
		{
			tmp = ft_free_str(tmp);
			break ;
		}
		tmp = expand_env_var_instr(tmp, tshell->env, tshell->exit_state);
		joined = ft_strjoin_free_fst(joined, tmp);
		joined = ft_strjoin_free_fst(joined, "\n");
		tmp = ft_free_str(tmp);
		rl_on_new_line();
	}
	if (fd > 2 && ft_strllen(joined))
		ft_printf_fd(fd, joined);
	joined = ft_free_str(joined);
	tshell->exit_state = 0;
	exit(0);
}
