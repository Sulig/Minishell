/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:40:04 by jguillot          #+#    #+#             */
/*   Updated: 2024/07/08 17:56:48 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens(t_token **toks)
{
	int	i;

	i = 0;
	while (toks && toks[i])
	{
		i++;
	}
	return (i);
}

char	*get_name_from_cmd(t_cmd *comand)
{
	t_token	*tok;

	tok = comand->name;
	return (tok->content);
}

char	**get_arr_input_from_cmd(t_cmd *comand)
{
	t_token	**tok;
	char	**arr;
	int		len;
	int		i;

	arr = NULL;
	tok = comand->input;
	len = count_tokens(tok);
	if (len == 0)
		return (NULL);
	arr = ft_calloc(sizeof(char *), len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = ft_strdup(tok[i]->content);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**get_arr_flags_from_cmd(t_cmd	*comand)
{
	t_token	**tok;
	char	**arr;
	int		len;
	int		i;

	arr = NULL;
	tok = comand->flags;
	len = count_tokens(tok);
	if (len == 0)
		return (NULL);
	arr = ft_calloc(sizeof(char *), len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = ft_strdup(tok[i]->content);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
