/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:54:26 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/24 19:11:46 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_all_arrstr(char **arr)
{
	size_t	i;

	i = 0;
	if (!ft_arr_strlen(arr))
		ft_printf_fd(1, "Null array\n");
	else
	{
		while (arr[i])
		{
			ft_printf_fd(1, "Pos |%u|: %s\n", i, arr[i]);
			i++;
		}
	}
}

void	print_tokens_st(t_list *tokens)
{
	size_t	size;
	t_token	*token;

	size = ft_lstsize(tokens);
	ft_printf("\n\tNumber of tokens: %u\n", size);
	size = 0;
	ft_printf("\t------------------\n\t----- TOKENS -----\n");
	while (tokens)
	{
		ft_printf(" ~ [%u] in list\t", size);
		token = (t_token *)tokens->content;
		ft_printf("~ toktype = '%c'\t", token->toktype);
		ft_printf("~ location/quoted = ");
		if (token->location == IN_DOUBLE_Q)
			ft_printf("IN DOUBLE QUOTES\t");
		else if (token->location == IN_SINGLE_Q)
			ft_printf("IN SINGLE QUOTES\t");
		else
			ft_printf("NO QUOTED\t");
		ft_printf("~ content '%s'\n", token->content);
		ft_printf("--------------------------------\n");
		tokens = tokens->next;
		size++;
	}
}

void	print_comands_st(t_list *cmd)
{
	size_t	size;
	t_cmd	*comand;

	size = ft_lstsize(cmd);
	ft_printf("\n\tNumber of comands: %u\n", size);
	size = 0;
	ft_printf("\t-------------------\n\t----- COMANDS -----\n");
	while (cmd)
	{
		ft_printf("~ Previous node: %p ~\n", cmd->prev);
		ft_printf("⎨---------------^---------------⎬\n");
		ft_printf("    [%u] Node: %p\n", size, cmd);
		comand = (t_cmd *)cmd->content;
		ft_printf("~ cmdtype = '%c'\t", comand->cmdtype);
		ft_printf("~ comand '%s'\n", comand->comand);
		ft_printf("~ options '%s'\n", comand->options);
		ft_printf("~ input: '%s'\n", comand->input);
		ft_printf("⎨---------------v---------------⎬\n");
		cmd = cmd->next;
		size++;
	}
}

void	print_multiple_cmds_st(t_list **cmds)
{
	size_t	size;

	size = 0;
	while (cmds[size])
	{
		ft_printf("~~~~~~~~~~~~ ~ Double linked list node pos: %u", size);
		ft_printf("\t~ Content: \033[38;5;%um\n", (size + 2) * 7);
		print_comands_st(cmds[size]);
		ft_printf(D);
		ft_printf("~~~~~~~~~~~~~ ~ ~~~~~~~~~~~~~~\n\n");
		size++;
	}
	ft_printf("Total size of double linked list: %u\n", size);
}
