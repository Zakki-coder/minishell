/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:34:34 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:35:19 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_variable(char **environ_cp, char *var_name)
{
	int		i;
	char	*var_value;

	i = 0;
	var_value = NULL;
	while (environ_cp[i]
		&& !ft_strnequ(environ_cp[i], var_name, ft_strlen(var_name)))
		++i;
	if (environ_cp[i] && environ_cp[i][ft_strlen(var_name)] == '=')
	{
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
		if (!var_value)
			error_exit("Malloc fail\n");
	}
	return (var_value);
}
