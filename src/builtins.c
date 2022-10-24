/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:36:02 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 15:56:33 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//env doesn't check the correctness of var name, at least on linux
int	update_env(const char *name, const char *value, char ***environ_cp)
{
	int		i;
	char	*name_value;

	i = 0;
	name_value = ft_memalloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!name_value)
		error_exit("Malloc fail\n");
	ft_strcpy(name_value, name);
	ft_strcat(name_value, "=");
	while ((*environ_cp)[i] && !ft_strnequ((*environ_cp)[i], name_value, ft_strlen(name_value)))
		++i;
	ft_strcat(name_value, value);
	if ((*environ_cp)[i])
	{
		free ((*environ_cp)[i]);
		(*environ_cp)[i] = name_value;
	}
	else
	{
		i = calc_chptr(*environ_cp);
		ft_realloc_darray((void ***)environ_cp, i, sizeof(**environ_cp) * (i + 2));
		(*environ_cp)[i] = name_value;
	}
	return (0);
}

int unset(char *name, char ***environ_cp)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (-1);
	var_name = ft_memalloc(ft_strlen(name) + 2);
	if (!var_name)
		error_exit("Malloc fail\n");
	ft_strcpy(var_name, name);
	ft_strcat(var_name, "=");
	while ((*environ_cp)[i] && !ft_strnequ((*environ_cp)[i], var_name, ft_strlen(var_name)))
		++i;
	if ((*environ_cp)[i])
	{
		ft_memdel((void **)&(*environ_cp)[i]);
		while ((*environ_cp)[i + 1])
		{
			(*environ_cp)[i] = (*environ_cp)[i + 1];
			++i;
		}
		(*environ_cp)[i] = (*environ_cp)[i + 1];
	}
	ft_memdel((void *)&var_name);
	return (0);
}
