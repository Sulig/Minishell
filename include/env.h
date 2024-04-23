/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/04/03 22:16:12 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/15 18:36:42 by jguillot         ###   ########.fr       */
=======
/*   Created: 2024/03/29 08:24:48 by jguillot          #+#    #+#             */
/*   Updated: 2024/03/30 08:43:45 by jguillot         ###   ########.fr       */
>>>>>>> Add files via upload
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

<<<<<<< HEAD
char	*get_var_from_env(const char *varname, char **env);
char	*find_var_line_from_env(const char *varname, char **env);
int     env_name_len(const char *str);
int	    find_var_index_from_env(char *elem, char **env);
char	*env_get_varname(const char *str);
int     env_valid_varname(char *word);
void	remove_env_var(char *varname, char **env);
char	**get_vars_from_env(const char *varname, char **env);

=======
// Usually used env var
# define USER "USER="
# define PWD "PWD="
# define OLDPWD "OLDPWD="
# define PATH "PATH="
# define HOME "HOME="

char	*env_get_var(const char *varname, char **env);
char	*env_find_var_line(const char *varname, char **env);
int	    env_name_len(const char *str);
char	**env_get_vars(const char *varname, char **env);
>>>>>>> Add files via upload
#endif