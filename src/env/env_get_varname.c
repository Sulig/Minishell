/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_varname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguillot <jguillot@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:10:09 by jguillot          #+#    #+#             */
/*   Updated: 2024/04/07 11:18:07 by jguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// Checks and returns TRUE if the given 'word' us a valid variable name.
// A valid name consists only of alphanumeric characters and underscores, and
// begins with an alphabetic character or an underscore.
int	env_valid_varname(char *word)
{
	if (!word || !*word)
		return (FALSE);
	if (*word == '_' || ft_isalpha(*word))
	{
		++word;
		while (*word == '_' || ft_isalnum(*word))
			++word;
	}
	if (!*word)
		return (TRUE);
	return (FALSE);
}

// Check if the string has a proper name for an environment variable before
// any '=' if exists.
// Allocates and returns the valid varname or NULL if invalid.
char	*env_get_varname(const char *str)
{
	int		len;
	char	*varname;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '='))
		len = ft_strlen(str);
	else
		len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	varname = ft_strdup(str);
	varname[len] = '\0';
	if (!env_valid_varname(varname))
	{
		free(varname);
		return (NULL);
	}
	return (varname);
}
