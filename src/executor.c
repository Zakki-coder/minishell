/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:11:48 by jakken            #+#    #+#             */
/*   Updated: 2022/11/02 20:40:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_builtin(char *cmd)
{
	return (ft_equstrlen(cmd, "echo")
		|| ft_equstrlen(cmd, "cd")
		|| ft_equstrlen(cmd, "setenv")
		|| ft_equstrlen(cmd, "unsetenv")
		|| ft_equstrlen(cmd, "env"));
}

static int	is_exit(char *cmd)
{
	return (ft_equstrlen(cmd, "exit"));
}

static void	update_last_exe_if_echo(char *cmd, char ***environ_cp, char **args)
{
	int		i;
	char	*new_value;

	i = 0;
	new_value = NULL;
	if (ft_equstrlen("echo", cmd))
	{
		if (args[1])
		{
			new_value = ft_strdup(args[++i]);
			while (args[++i])
			{
				new_value = (char *)ft_realloc((void *)new_value,
						ft_strlen(new_value) + 1, ft_strlen(new_value)
						+ ft_strlen(args[i]) + 3);
				ft_strcat(new_value, " ");
				ft_strcat(new_value, args[i]);
			}
		}
		else
			new_value = ft_strdup("echo");
		update_env("_", new_value, environ_cp);
		ft_memdel((void **)&new_value);
	}
}

static void	update_last_exe(char *cmd, char ***environ_cp)
{
	if (cmd && !ft_equstrlen("echo", cmd))
		update_env("_", cmd, environ_cp);
}

void	executor(char **args, char ***environ_cp)
{
	update_last_exe(args[0], environ_cp);
	if (is_exit(args[0]))
		ms_exit(args, environ_cp);
	if (is_builtin(args[0]))
		exe_builtins(args, environ_cp);
	else
		execute_bin(args, environ_cp);
	update_last_exe_if_echo(args[0], environ_cp, args);
}
