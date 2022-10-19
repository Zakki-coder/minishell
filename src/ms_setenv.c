/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:31:35 by jakken            #+#    #+#             */
/*   Updated: 2022/10/19 19:07:25 by jakken           ###   ########.fr       */
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

/* If variable is given without eq. I.e <VARNAME> <VALUE> dont check the value */
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

int	ms_setenv(char **args, char **environ_cp)
{
	int		i;
	char	*eq;
	char	*name;

	i = 1;
	if (!validate_args(args))
		return (0);
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
				update_env(args[i], args[++i], environ_cp);
			else
				update_env(args[i], "", environ_cp);
		}
		++i;
	}
}
