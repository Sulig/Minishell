/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:04:35 by jguillot          #+#    #+#             */
/*   Updated: 2024/03/25 23:56:37 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "minishell.h"

t_cmd	*lst_move(t_cmd *node, int n);
void	lst_rm_many(t_cmd *lst, t_cmd *to_rm, size_t n);
void	lst_delone(t_cmd *lst);
void	lst_link(t_cmd *n1, t_cmd *n2);
size_t	lst_size(t_cmd *lst);

#endif