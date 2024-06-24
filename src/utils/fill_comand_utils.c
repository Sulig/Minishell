/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_comand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:20:47 by sadoming          #+#    #+#             */
/*   Updated: 2024/06/24 19:28:07 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	len_of_tokens(t_token **arr)
{
	size_t	size;

	size = 0;
	if (!arr)
		return (0);
	while (arr[size])
		size++;
	return (size);
}

t_token	**push_intoarr(t_token **original, t_token *add)
{
	t_token	**new_arr;
	size_t	size;

	size = len_of_tokens(original);
	new_arr = ft_calloc(sizeof(t_token *), size + 2);
	if (!new_arr)
		return (print_err_custom(MERR_MALLOC, 1));
	return (new_arr);
}

t_token	**pop_outarr(t_token **original, size_t pop)
{
	t_token	**new_arr;
	size_t	size;

	size = len_of_tokens(original);
	new_arr = ft_calloc(sizeof(t_token *), size - 1);
	if (!new_arr)
		return (print_err_custom(MERR_MALLOC, 1));
	return (new_arr);
}
