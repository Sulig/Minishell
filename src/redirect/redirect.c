/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:19:11 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/09 22:56:41 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Performs the redirection defined by 'redir', taking 'next' as the following 
// token, knowing it's the 'n'-th command.
// In the case of here documents, quote-removal is performed.
// Returns the appropriate exit code after printing any error message.
static int	redirect_one(t_cmd *redir)//, t_list *next, int n)
{
	char	*str;

	if (redir->output == NULL)
	{
		print_err_syntax("ambiguous redirect");
        return (EXIT_FAILURE);
	}
	str = redir->output;
	if (!ft_strncmp(redir->comand, ">", 2))
		return (link_output_file(str, FALSE));
    else if (!ft_strncmp(redir->comand, ">>", 3))
		return (link_output_file(str, TRUE));
		/*
	else if (!ft_strncmp(redir, "<", 2))
		return (link_input_file(str));
	else if (!ft_strncmp(redir, "<<", 3))
		return (link_heredoc(n));
        */
	return (EXIT_FAILURE);
}

// Performs all redirections of 'cmd', from left-to-right, removing the
// redirection tokens, knowing it's the 'n'-th command. Returns the exit status.
// If a redirection error ocurrs, prints an error message.
int	redirect(t_list *cmd, int n)
{
	int		exit_status;
	t_cmd	*node;
	t_list *lst;

	exit_status = 0;
	lst = cmd;
	node = lst->content;
	while (lst && exit_status == 0)
	{
		node = lst->content;
		if (node->cmdtype == REDIR)
		{
			exit_status = redirect_one(node);
			lst = lst->next;
		}
		else
            lst = lst->next;
	}

	return (exit_status);
}
