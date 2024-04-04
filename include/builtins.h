/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:25:38 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/03 18:53:54 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*BUILTINS UTILS*/
int is_builtin_name(const char *str);

/* BUILTINS */
int builtin_echo(t_cmd *cmd);
int	builtin_pwd(void);

#endif