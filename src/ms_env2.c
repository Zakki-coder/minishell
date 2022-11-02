/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:52:30 by jakken            #+#    #+#             */
/*   Updated: 2022/11/02 13:52:23 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_set_var(char **args, char ***environ_cp, int *i, int flags)
{
	char	**name_val;
	char	*eq;

	while (args[*i])
	{
		name_val = NULL;
		eq = NULL;
		eq = ft_strchr(args[*i], '=');
		if (eq)
			name_val = ft_strsplit(args[*i], '=');
		else
			break ;
		if (name_val[0] && name_val[1])
			update_env(name_val[0], name_val[1], environ_cp);
		else if (name_val[0])
			update_env(name_val[0], "", environ_cp);
		else if (eq)
			update_env("=", "", environ_cp);
		ft_freeda((void ***)&name_val, calc_chptr(name_val));
		if (flags & ENV_V)
			ft_printf("setenv:\t%s\n", (*environ_cp)[calc_chptr(*environ_cp)]);
		++(*i);
	}
}

static int	env_get_flag(char **args, int i, int flags)
{
	if (ft_equstrlen(args[i], "-v"))
		flags |= ENV_V;
	else if (ft_equstrlen(args[i], "-i"))
		flags |= ENV_I;
	else if (ft_equstrlen(args[i], "-u"))
		flags |= ENV_U;
	else if (ft_equstrlen(args[i], "-C"))
		flags |= ENV_C;
	else
	{
		ft_printf("env: unrecognized option '%s'\n", args[i]);
		return (-1);
	}
	return (flags);
}

static int	env_flags_parse(char **args, int delimit)
{
	int	flags;
	int	i;

	flags = 0;
	i = 1;
	while (args[i] && i < delimit)
	{
		if (args[i][0] == '-')
			flags = env_get_flag(args, i, flags);
		++i;
	}
	return (flags);
}

int	env_flags(char **args, char **environ_cp, int *i)
{
	int		delimit;
	char	*cmd;
	int		flags;

	*i = 1;
	delimit = 1;
	cmd = NULL;
	while (args[delimit])
	{
		cmd = search_bin(args[delimit], environ_cp);
		if (cmd || ft_strchr(args[delimit], '='))
		{
			ft_memdel((void **)&cmd);
			break ;
		}
		++delimit;
	}
	flags = env_flags_parse(args, delimit);
	*i = delimit;
	return (flags);
}
