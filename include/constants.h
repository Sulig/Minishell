/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:04:37 by sadoming          #+#    #+#             */
/*   Updated: 2024/05/01 21:12:53 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/*	PROMPTS	*/
# define PROMPT "minishell: "
# define HEREDOC "heredoc> "

/*	MENSAGE ERRORS	*/
# define MERR_MALLOC "Insuficient Memory or Malloc Error"
# define MERR_NOPATH "PATH not finded!"
# define MERR_FORK "Fork failed"
# define MERR_FILE "No such file or directory"
# define MERR_UNSET "unset: error getting env var"
# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_HEREDOC_ERR "cannot create temp file for here document"

#endif
