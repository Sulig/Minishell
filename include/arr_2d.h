/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_2d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:02:30 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/10 19:52:22 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_2D_H
# define ARR_2D_H

int		arr_2d_len(char **arr);
void	free_arr_2d(char **arr);
char	**remove_last_elem_arr2d(char **arr);
char	**append_arr_2d(char **arr, char *s);
char	**remove_elem_arr2d(char **arr, int i);

#endif
