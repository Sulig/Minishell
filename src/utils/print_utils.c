/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:54:26 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/08 18:11:54 by sadoming         ###   ########.fr       */
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
	ft_printf("\tNumber of tokens: %u\n", size);
	size = 0;
	ft_printf("\t----------------\n\t---- TOKENS ----\n");
	while (tokens)
	{
		ft_printf(" ~ [%u] in list\t", size);
		token = (t_token *)tokens->content;
		ft_printf("~ toktype = '%c'\t", token->toktype);
		ft_printf("~ content '%s'\n", token->content);
		ft_printf("--------------------------------\n");
		tokens = tokens->next;
		size++;
	}
}
