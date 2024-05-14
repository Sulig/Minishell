/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:45:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/14 16:32:12 by jguillot         ###   ########.fr       */
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

void	heredoc(char **env, char *end, int fd)
{
	char	*tmp;
	char	*joined;

	(void)env;
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
		//Expand env_vars
		joined = ft_strjoin_free_fst(joined, tmp);
		tmp = ft_free_str(tmp);
	}
	if (fd > 2)
		ft_printf_fd(fd, joined);
	joined = ft_free_str(joined);
}
