/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:34:34 by jakken            #+#    #+#             */
/*   Updated: 2022/11/02 13:43:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Retruns the value of the variable, i.e everything after =*/
char	*search_variable(char **environ_cp, char *var_name)
{
	int		i;
	char	*var_value;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	var_value = NULL;
	while (environ_cp[i]
		&& !(ft_strnequ(environ_cp[i], var_name, len)
			&& environ_cp[i][len] == '='))
		++i;
	if (environ_cp[i] && environ_cp[i][len] == '=')
	{
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
		if (!var_value)
			error_exit("Malloc fail\n");
	}
	return (var_value);
}
