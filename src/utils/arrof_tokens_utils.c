/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrof_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:20:47 by sadoming          #+#    #+#             */
/*   Updated: 2024/07/03 19:53:11 by sadoming         ###   ########.fr       */
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

t_token	*duplicate_token(t_token *org)
{
	t_token	*dup;

	if (!org)
		return (NULL);
	dup = ft_calloc(sizeof(t_token), 1);
	if (!dup)
		return (NULL);
	dup->toktype = org->toktype;
	dup->location = org->location;
	dup->content = ft_strdup(org->content);
	return (dup);
}

t_token	**push_intoarr(t_token **original, t_token *add)
{
	t_token	**new_arr;
	size_t	size;
	size_t	i;

	i = -1;
	size = len_of_tokens(original);
	new_arr = ft_calloc(sizeof(t_token *), size + 2);
	if (!new_arr)
		return (NULL);
	while (++i < size)
		new_arr[i] = duplicate_token(original[i]);
	new_arr[i] = duplicate_token(add);
	original = clear_tarr(original);
	return (new_arr);
}

t_token	**pop_outarr(t_token **original, size_t pop)
{
	t_token	**new_arr;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	size = len_of_tokens(original) - 1;
	if (!size)
	{
		original = clear_tarr(original);
		return (NULL);
	}
	new_arr = ft_calloc(sizeof(t_token *), size - 1);
	if (!new_arr)
		return (NULL);
	while (original[++j])
		if (j != pop)
			new_arr[i++] = duplicate_token(original[j]);
	original = clear_tarr(original);
	return (new_arr);
}

t_token	**clear_tarr(t_token **to_clear)
{
	t_token	*token;
	size_t	p;

	p = 0;
	if (!to_clear)
		return (NULL);
	while (to_clear[p])
	{
		token = to_clear[p];
		token->content = ft_free_str(token->content);
		free(token);
		token = NULL;
		p++;
	}
	free(to_clear);
	to_clear = NULL;
	return (NULL);
}
