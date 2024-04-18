/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:43 by sadoming          #+#    #+#             */
/*   Updated: 2024/04/18 20:04:23 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_strgroup(char *str, size_t *pos, int *quote)
{
	char	*tmp;
	size_t	i;
	int		saved;

	i = *pos + 1;
	saved = *quote;
	tmp = NULL;
	while (str[i] && *quote == saved)
	{
		*quote = set_quote(str[i], *quote);
		if (*quote != saved)
			break ;
		i++;
	}
	tmp = ft_substr(str, *pos + 1, i - 1 - *pos);
	if (!ft_strllen(tmp))
		tmp = ft_free_str(tmp);
	*pos = i - 1;
	return (tmp);
}

void	create_first_noqgroup(char *str, t_list **noq_groups, size_t *pos)
{
	size_t	dq_pos;
	size_t	sq_pos;
	char	*tmp;

	tmp = NULL;
	dq_pos = ft_cnttoch_out(str, '\"');
	sq_pos = ft_cnttoch_out(str, '\'');
	if (dq_pos < sq_pos)
	{
		tmp = ft_substr(str, 0, dq_pos);
		*pos = dq_pos;
	}
	if (sq_pos < dq_pos)
	{
		tmp = ft_substr(str, 0, sq_pos);
		*pos = sq_pos;
	}
	if (!ft_strllen(tmp))
		tmp = ft_free_str(tmp);
	if (tmp)
		*noq_groups = ft_lstnew(tmp);
}

static t_list	*create_noqgroups(char *str)
{
	t_list	*unquoted_groups;
	t_list	*tmp;
	size_t	i;
	int		quoted;

	i = 0;
	quoted = 0;
	tmp = NULL;
	unquoted_groups = NULL;
	if (ft_cnttoch_out(str, '\'') != 0 || ft_cnttoch_out(str, '\"') != 0)
		create_first_noqgroup(str, &unquoted_groups, &i);
	while (str[i])
	{
		quoted = set_quote(str[i], quoted);
		tmp = ft_lstnew(create_strgroup(str, &i, &quoted));
		ft_lstadd_back(&unquoted_groups, tmp);
		i++;
	}
	return (unquoted_groups);
}

t_cmd	*quote_removal_comand(t_cmd *cmd)
{
	t_list	*unquoted_groups;
	t_list	*iterate;
	char	*tmp;

	unquoted_groups = NULL;
	if (!ft_strllen(cmd->comand))
		return (cmd);
	if (!ft_strchr(cmd->comand, '\"') && !ft_strchr(cmd->comand, '\''))
		return (cmd);
	unquoted_groups = create_noqgroups(cmd->comand);
	iterate = unquoted_groups;
	while (iterate)
	{
		tmp = (char *)iterate->content;
		ft_printf("Content: %s\n", tmp);
		iterate = iterate->next;
	}
	return (cmd);
}
