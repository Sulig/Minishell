/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnodepos_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:50:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/03/28 17:20:45 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/list.h"

size_t	ft_lstpos_node(t_list *lst, t_list *node)
{
	size_t	pos;

	pos = 0;
	if (!lst)
		return (0);
	if (!node)
		return (ft_lstsize(lst));
	while (lst)
	{
		if (node == lst)
			return (pos);
		lst = lst->next;
		pos++;
	}
	return (pos);
}

t_list	*ft_lstgetnode(t_list *lst, size_t pos)
{
	size_t	i;

	i = 0;
	while (i < pos)
	{
		if (lst)
			lst = lst->next;
		i++;
	}
	return (lst);
}

t_list	*ft_asign_nodepos(t_list *lst)
{
	t_list	*first;
	size_t	pos;

	first = lst;
	pos = 0;
	while (lst)
	{
		lst->pos = pos;
		lst = lst->next;
		pos++;
	}
	return (first);
}
