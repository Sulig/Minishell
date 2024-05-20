/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:28:49 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/20 18:46:30 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Helper function to count occurrences of a substring in a string
int	count_occurrences(char *str, const char *sub)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (ft_strstr(tmp, sub) != NULL)
	{
		tmp = ft_strstr(tmp, sub);
		count++;
		tmp += ft_strlen(sub);
	}
	return (count);
}

char	*replace(char *str, char *result, char *exit_status_str)
{
	char	*src;
	char	*dst;
	int		len;

	src = str;
	dst = result;
	while (ft_strstr(src, "$?") != NULL)
	{
		src = ft_strstr(src, "$?");
		len = src - str;
		ft_strncpy(dst, str, len);
		dst += len;
		src += 2;
		ft_strcpy(dst, exit_status_str);
		dst += strlen(exit_status_str);
		str = src;
	}
	ft_strcpy(dst, str);
	return (result);
}

char	*replace_exit_st(char *str, int exit_status)
{
	char	*exit_status_str;
	int		occ;
	int		new_len;
	char	*result;

	exit_status_str = ft_itoa(exit_status);
	occ = count_occurrences(str, "$?");
	if (occ == 0)
		return (str);
	new_len = ft_strlen(str) + occ * (ft_strlen(exit_status_str) - 2) + 1;
	result = (char *)malloc(new_len);
	if (result == NULL)
		exit(EXIT_FAILURE);
	result = ft_strdup(replace(str, result, exit_status_str));
	free(exit_status_str);
	return (result);
}

void	change_to_exit_status(t_list *tokens, int ex_st)
{
	t_list	*first;
	t_token	*node;

	first = tokens;
	while (tokens)
	{
		node = tokens->content;
		if (ft_strstr(node->content, "$?") && node->location != IN_SINGLE_Q)
		{
			node->content = ft_strdup(replace_exit_st(node->content, ex_st));
		}
		tokens = tokens->next;
	}
	tokens = first;
}
