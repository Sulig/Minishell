/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:43:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/17 19:14:05 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_quote(char ch, int quoted)
{
	if (ch == '\'')
	{
		if (!quoted)
			return (1);
		else if (quoted == 1)
			return (0);
	}
	if (ch == '\"')
	{
		if (!quoted)
			return (2);
		if (quoted == 2)
			return (0);
	}
	return (quoted);
}

static char	*trim_the_input(char *input, size_t start, size_t end)
{
	char	*cut_st;
	char	*cut_ed;
	char	*result;

	cut_st = ft_strcpyl(input, start);
	cut_ed = ft_strdup(input + end);
	result = ft_strjoin_s(cut_st, cut_ed);
	cut_st = ft_free_str(cut_st);
	cut_ed = ft_free_str(cut_ed);
	input = ft_free_str(input);
	return (result);
}

static char	*trim_inside(char *str)
{
	size_t	i;
	size_t	pos;
	int		quote;

	i = 0;
	quote = 0;
	if (!ft_strllen(str))
		return (ft_free_str(str));
	while (str[i])
	{
		quote = set_quote(str[i], quote);
		if (str[i] == ' ' && !quote)
		{
			pos = ++i;
			while (str[i] && str[i] == ' ')
				i++;
			str = trim_the_input(str, pos, i);
			i = pos - 1;
		}
		i++;
	}
	return (str);
}

t_cmd	*trim_input(t_cmd *cmd)
{
	char	*trim;

	if (!ft_strllen(cmd->input))
		return (cmd);
	trim = ft_strtrim_s(cmd->input, " ");
	cmd->input = ft_strremplace(cmd->input, trim);
	trim = ft_free_str(trim);
	cmd->input = trim_inside(cmd->input);
	return (cmd);
}
