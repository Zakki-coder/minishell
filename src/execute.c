/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:18 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:35:25 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**add_cwd_to_path(char **environ_cp)
{
	char	*path;
	char	*new;
	char	**bk;

	bk = ft_cpynstrarr(environ_cp, calc_chptr(environ_cp));
	path = search_variable(environ_cp, "PATH");
	if (!path)
	{
		update_env("PATH", ".", &bk);
		return (bk);
	}
	new = ft_strjoin(path, ":.");
	ft_memdel((void **)&path);
	update_env("PATH", new, &bk);
	ft_memdel((void **)&new);
	return (bk);
}

int	execute_bin(char **args, char **environ_cp)
{
	char	*cmd;
	int		id;
	int		wstatus;
	char	**environ_bk;

	if (!*args)
		return (0);
	environ_bk = add_cwd_to_path(environ_cp);
	cmd = search_bin(args[0], environ_bk);
	if (cmd)
	{
		id = fork();
		if (id == 0)
			execve(cmd, args, environ_cp);
		else if (id < 0)
			error_exit("minishell: Forking failed\n");
		else
			wait(&wstatus);
	}
	else
		ft_printf("minishell: %s: command not found...\n", args[0]);
	ft_memdel((void **)&cmd);
	return (0);
}
