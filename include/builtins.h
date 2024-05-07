/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:25:38 by jguillot          #+#    #+#             */
/*   Updated: 2024/05/07 20:32:41 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define LLINT_MIN_STR "9223372036854775808"
# define LLINT_MAX_STR "9223372036854775807"

/* BUILTINS */
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_cd(t_cmd *cmd, char **env);
int		builtin_env(char **env);
int		builtin_export(t_cmd *cmd, t_shell *tshell);
int		builtin_unset(t_cmd *cmd, char **env);
int		builtin_exit(t_cmd *cmd);

/* UTILS */
int		is_builtin_cmd(t_list *cmd_lst);
char	**change_pwd_home(char **env);
char	**change_oldpwd(char *pwd, char **my_env);
char	**change_pwd_absolute(char *path, char **env);
char	**change_pwd_relative(char *path, char **my_env);
char	**change_pwd(char **temp, char **env);
char	*concat_path(char **env, char *str);

#endif
