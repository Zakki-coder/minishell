/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:22:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/11 14:45:27 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env(char **var, char **environ_cp)
{
	int		i;
	char	*var_value;
	char	*needle;

	i = 0;
	// USE STRN TO COMPARE JUST FOR THE START OF THE STR AND CHECK THAT = IS NEXT
	while (environ_cp[i] ))
		++i;
	if (!environ_cp[i])
		var_value = ft_strdup("");
	else
		var_value = ft_strdup()

}

int is_accepted_variable_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

/* Every legal var name char after $ is considered as part of variable name */
/* The name of a variable can contain only letters (a to z or A to Z), numbers ( 0 to 9) or the underscore character ( _). */
int parse_variable(char *usd, char **dst)
{
	char	*parsed;
	int		i;

	i = 0;
	if (usd[i] == '$')
		++i;
	while (is_accepted_variable_char(usd[i]))
		++i;
	if (i == 1)
	{
		*dst = ft_strdup("");
		return (i);
	}
	*dst = ft_strsub(usd, 0, i);
	if (!(*dst))
		error_exit("Malloc fail\n");
	return (i);
}