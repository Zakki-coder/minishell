/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:11:48 by jakken            #+#    #+#             */
/*   Updated: 2022/10/18 16:37:12 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_equstrlen(cmd, "echo")
		|| ft_equstrlen(cmd, "cd")
		|| ft_equstrlen(cmd, "setenv")
		|| ft_equstrlen(cmd, "unsetenv")
		|| ft_equstrlen(cmd, "env")
		|| ft_equstrlen(cmd, "exit"));
}

void	executor(char **args, char **environ_cp)
{
	if (is_builtin(args[0]))
		exe_builtins(args, environ_cp);
	else
		execute_bin(args, environ_cp);
}
