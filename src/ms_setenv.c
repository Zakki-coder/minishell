/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:31:35 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:22:25 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_name(char *var)
{
	if (ft_isdigit(var[0]))
	{
		ft_printf("setenv: Variable name must begin with a letter.\n");
		return (0);
	}
	while (*var)
	{
		if (!is_varchr(*var))
		{
			ft_printf("setenv: Variable name must\
					contain alphanumeric characters.\n");
			return (0);
		}
		++var;
	}
	return (1);
}

static	int	validate_args(char **args)
{
	int		i;
	char	*eq;
	char	*sub;
	int		ret;

	i = 1;
	ret = 1;
	while (args[i] && ret)
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			sub = ft_strsub(args[i], 0, eq - args[i]);
			ret = check_var_name(sub);
			ft_memdel((void **)&sub);
		}
		else
		{
			ret = check_var_name(args[i]);
			if (ret && args[i + 1] && !ft_strchr(args[i + 1], '='))
				++i;
		}
		++i;
	}
	return (ret);
}

static void	setter(char **args, char ***environ_cp, char *eq, char *name)
{
	int	i;

	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			name = ft_strsub(args[i], 0, eq - args[i]);
			update_env(name, eq + 1, environ_cp);
			ft_memdel((void **)&name);
		}
		else
		{
			if (args[i + 1] && !ft_strchr(args[i + 1], '='))
			{
				update_env(args[i], args[i + 1], environ_cp);
				++i;
			}
			else
				update_env(args[i], "", environ_cp);
		}
		++i;
	}
}

int	ms_setenv(char **args, char ***environ_cp)
{
	char	*eq;
	char	*name;

	if (!validate_args(args))
		return (0);
	eq = NULL;
	name = NULL;
	setter(args, environ_cp, eq, name);
	return (1);
}
