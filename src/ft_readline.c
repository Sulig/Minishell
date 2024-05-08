/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:45:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/08 19:59:25 by sadoming         ###   ########.fr       */
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

static char	*fline(size_t _case)
{
	static size_t	bruh;
	char			*ttp;

	if (_case)
		bruh = _case;
	if (!bruh)
		ttp = "hello";
	else if (bruh == 1)
		ttp = "$USER";
	else if (bruh == 2)
		ttp = "sometext $USER";
	else if (bruh == 3)
		ttp = "$USER sometext";
	else if (bruh == 4)
		ttp = "sometext $USER sometext";
	else
		ttp = "EOF";
	bruh++;
	return (ft_strdup(ttp));
}

void	heredoc(t_shell *tshell, char *end, int fd)
{
	char	*tmp;
	char	*joined;

	joined = NULL;
	while (4)
	{
		//tmp = readline(HEREDOC);
		tmp = fline(0);
		if (!tmp)
			break ;
		if (my_strcmp(end, tmp))
		{
			tmp = ft_free_str(tmp);
			break ;
		}
		tmp = expand_env_var_instr(tmp, tshell->env, tshell->exit_state);
		joined = ft_strjoin_free_fst(joined, tmp);
		tmp = ft_free_str(tmp);
		//break ;
	}
	if (fd > 2)
		ft_printf_fd(fd, joined);
	joined = ft_free_str(joined);
}
