/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:22:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/25 19:31:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_var_with_value(char **var_name, char **environ_cp)
{
	int		i;
	char	*var_value;
	char	*var;

	i = 0;
	var = search_variable(environ_cp, *var_name);
	if (var)
		var_value = ft_strdup(var);
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
