/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:39:50 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 15:40:37 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	char_to_builtin(char *arg)
{
	unsigned	len;

	len = ft_strlen(arg);
	if (ft_strlen("echo") == len && ft_strequ("echo", arg))
		return (ECHO);
	else if (ft_strlen("env") == len && ft_strequ("env", arg))
		return (ENV);
	else if (ft_strlen("setenv") == len && ft_strequ("setenv", arg))
		return (SETENV);
	else if (ft_strlen("cd") == len && ft_strequ("cd", arg))
		return (CD);
	else if (ft_strlen("exit") == len && ft_strequ("exit", arg))
		return (EXIT);
	else if (ft_strlen("unsetenv") == len && ft_strequ("unsetenv", arg))
		return (UNSETENV);
	return (-1);
}

// There is nothing in p array index zero at the moment, because env takes two args
// All of these should propably return int to somewhere
void	exe_builtins(char **args, char ***environ_cp)
{
	int cmd;

	cmd = char_to_builtin(args[0]);
	if (cmd == ENV)
		ms_env(args, *environ_cp);
	else if (cmd == CD)
		ms_cd(args, environ_cp);
	else if (cmd == SETENV)
		ms_setenv(args, environ_cp);
	else if (cmd == EXIT)
		ms_exit(args, *environ_cp);
	else if (cmd == UNSETENV)
		ms_unsetenv(args, environ_cp);
	else if (cmd == ECHO)
		ms_echo(args);
	else
		ft_printf("minishell: %s: command not found...\n", args[0]);
}
