/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:16:12 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/25 12:50:55 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	*get_var_from_env(const char *varname, char **env);
char	*find_var_line_from_env(const char *varname, char **env);
int		env_name_len(const char *str);
int		find_var_index_from_env(char *elem, char **env);
char	*env_get_varname(const char *str);
int		env_valid_varname(char *word);
void	remove_env_var(char *varname, char **env);
char	**get_vars_from_env(const char *varname, char **env);
void	env_set_var(const char *varname, const char *value, char **env);

#endif
