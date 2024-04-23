/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:15:53 by jguillot          #+#    #+#             */
/*   Updated: 2024/03/30 09:21:17 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define LLINT_MIN_STR "9223372036854775808"
# define LLINT_MAX_STR "9223372036854775807"

/* BUILTINS */
int echo_builtin(char **args);
int	pwd_builtin(void);
int	cd_builtin(char **args, char **env);
int	exit_builtin(char **args, int exit_status, int is_child);

/* BUILTINS UTILS */
int exec_builtin(char **args, t_shell *tshell, int is_child);


#endif