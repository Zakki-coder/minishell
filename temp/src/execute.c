/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:18 by jakken            #+#    #+#             */
/*   Updated: 2022/11/02 11:48:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exe_fail(char **cmd, char **args, char ***env_cp)
{
	ft_printf("minishell: %s: command not found...\n", args[0]);
	ft_memdel((void **)cmd);
	ms_exit(args, env_cp);
}

static int	check_if_user_exe(char *cmd, char **dest)
{
	*dest = NULL;
	if (ft_strchr(cmd, '/'))
	{
		*dest = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

int	execute_bin(char **args, char ***environ_cp)
{
	char	*cmd;
	int		id;
	int		wstatus;

	if (!args[0])
		return (0);
	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	if (!cmd || !ft_strchr(cmd, '/'))
		ft_printf("minishell: %s: command not found...\n", args[0]);
	else
	{
		id = fork();
		if (id == 0)
		{
			if (!cmd || execve(cmd, args, *environ_cp) < 0)
				exe_fail(&cmd, args, environ_cp);
		}
		else if (id < 0)
			error_exit("minishell: Forking failed\n");
		else
			wait(&wstatus);
	}
	ft_memdel((void **)&cmd);
	return (0);
}
