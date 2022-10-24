/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:22:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/24 15:31:24 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_var_with_value(char **var_name, char **environ_cp)
{
	int		i;
	char	*var_value;
	char	*var;

	i = 0;
	var = ft_memalloc(ft_strlen(*var_name) + 2);
	if (!var)
		error_exit("Malloc fail\n");
	ft_strcpy(var, *var_name);
	ft_strcat(var, "=");
	while (environ_cp[i]
		&& !ft_strnequ(environ_cp[i], var, ft_strlen(var)))
		++i;
	if (environ_cp[i] && environ_cp[i][ft_strlen(*var_name)] == '=')
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
	else
		var_value = ft_strdup("");
	free (*var_name);
	ft_memdel((void **)&var);
	*var_name = var_value;
}

static int	is_accepted_variable_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

/* Every legal var name char after $ is considered as part of variable name */
/* The name of a variable can contain only letters (a to z or A to Z),
	numbers ( 0 to 9) or the underscore character ( _). */
int	parse_variable(char *usd, char **dst)
{
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
	*dst = ft_strsub(usd, 1, i - 1);
	if (!(*dst))
		error_exit("Malloc fail\n");
	return (i);
}
