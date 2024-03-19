/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfor_unclosedquotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:59:11 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/19 19:47:39 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long	unclosed_squote(char *line)
{
	size_t	i;
	size_t	s_quotes;
	long	pos;

	i = 0;
	pos = 0;
	s_quotes = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			pos = i;
			s_quotes++;
		}
		i++;
	}
	if (s_quotes % 2)
		return (pos);
	return (-1);
}

long	unclosed_dquote(char *line)
{
	size_t	i;
	size_t	d_quotes;
	long	pos;

	i = 0;
	pos = 0;
	d_quotes = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\"')
		{
			pos = i;
			d_quotes++;
		}
		i++;
	}
	if (d_quotes % 2)
		return (pos);
	return (-1);
}

int	checkfor_unclosedquotes(char *line)
{
	long	where_d;
	long	where_s;
	long	where;

	where_d = unclosed_dquote(line);
	where_s = unclosed_squote(line);
	if (where_d == -1 || (where_s < where_d && where_s != -1))
		where = where_s;
	if (where_s == -1 || (where_d < where_s && where_d != -1))
		where = where_d;
	if (where != -1)
		return (print_err_syntax(line + where));
	return (1);
}
