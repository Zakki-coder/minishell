/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:11:48 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:27:27 by jakken           ###   ########.fr       */
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

void	executor(char **args, char ***environ_cp)
{
	if (is_exit(args[0]))
		ms_exit(args, *environ_cp);
	if (is_builtin(args[0]))
		exe_builtins(args, environ_cp);
	else
		execute_bin(args, *environ_cp);
}
