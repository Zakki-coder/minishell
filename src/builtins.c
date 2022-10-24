/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:36:02 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 17:04:54 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//env doesn't check the correctness of var name, at least on linux
int	update_env(const char *name, const char *value, char ***env)
{
	int		i;
	char	*nam_val;

	i = 0;
	nam_val = ft_memalloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!nam_val)
		error_exit("Malloc fail\n");
	ft_strcpy(nam_val, name);
	ft_strcat(nam_val, "=");
	while ((*env)[i] && !ft_strnequ((*env)[i], nam_val, ft_strlen(nam_val)))
		++i;
	ft_strcat(nam_val, value);
	if ((*env)[i])
	{
		free ((*env)[i]);
		(*env)[i] = nam_val;
	}
	else
	{
		i = calc_chptr(*env);
		ft_realloc_darray((void ***)env, i, sizeof(**env) * (i + 2));
		(*env)[i] = nam_val;
	}
	return (0);
}

int	unset(char *name, char ***env)
{
	char	*var;
	int		i;

	i = 0;
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (-1);
	var = ft_memalloc(ft_strlen(name) + 2);
	if (!var)
		error_exit("Malloc fail\n");
	ft_strcpy(var, name);
	ft_strcat(var, "=");
	while ((*env)[i] && !ft_strnequ((*env)[i], var, ft_strlen(var)))
		++i;
	if ((*env)[i])
	{
		ft_memdel((void **)&(*env)[i]);
		while ((*env)[i + 1])
		{
			(*env)[i] = (*env)[i + 1];
			++i;
		}
		(*env)[i] = (*env)[i + 1];
	}
	ft_memdel((void *)&var);
	return (0);
}
