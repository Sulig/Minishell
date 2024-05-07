/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:35:51 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/07 17:18:06 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHERS_H
# define SEARCHERS_H

/* SEARCHERS */
int		my_strcmp(const char *str, const char *cmp);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

size_t	ft_cnt_tostr(const char *haystack, const char *needle);
size_t	ft_cnt_tostr_end(const char *haystack, const char *needle);
size_t	ft_search_str(char **arr, char *to_search);

size_t	ft_apears_ch_in_str(char *str, char ch);
size_t	ft_apears_str_in_str(const char *haystack, const char *needle);

#endif
