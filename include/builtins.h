/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:25:38 by jguillot          #+#    #+#             */
/*   Updated: 2024/06/18 12:57:28 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define LLINT_MIN_STR "9223372036854775808"
# define LLINT_MAX_STR "9223372036854775807"

/* BUILTINS */
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_cd(t_cmd *cmd, t_shell *tshell);
int		builtin_env(char **env);
int		builtin_export(t_cmd *cmd, t_shell *tshell);
int		builtin_unset(t_cmd *cmd, t_shell *tshell);
int		builtin_exit(t_cmd *cmd, int exit_status, int is_child);

/* UTILS */
int		is_builtin_cmd(t_list *cmd_lst);
char	**change_pwd_home(char **env);
void	change_oldpwd(t_shell *tshell);
void	change_pwd_to_home(t_shell *tshell);
int		change_pwd(t_shell *tshell);
char	*concat_path(char **env, char *str);
char	**get_key_value_pair(char *arg);
void	change_pwds(t_shell *tshell);
void	change_pwds_home(t_shell *tshell);
int		check_cd_input (t_cmd *cmd, t_shell *tshell);

#endif
