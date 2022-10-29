/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:18 by jakken            #+#    #+#             */
/*   Updated: 2022/10/29 21:08:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
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
*/

static void	exe_fail(char **cmd, char **args, char ***env_cp)
{
	ft_printf("minishell: %s: command not found...\n", args[0]);
	ft_memdel((void **)cmd);
	ms_exit(args, env_cp);
}

static int count_char(char *str, char c)
{
	int	i;

	i = 0;
	while(*str)
	{
		if (*str == c)
			++i;
		++str;
	}
	return (i);
}

/*
static char	*search_cmd_from_cwd(char *cmd, char **environ_cp)
{
	char	*cwd;
	char	**bk;
	char	*res;

	res = NULL;
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		bk = ft_cpynstrarr(environ_cp, calc_chptr(environ_cp));
		cwd_wrap(&cwd);
		update_env("PATH", cwd, &bk);
		res = search_bin(cmd, bk);
		ft_freeda((void ***)&bk, calc_chptr(bk));
	}
	return (res);
}
*/

int	execute_bin(char **args, char ***environ_cp)
{
	char	*cmd;
	int		id;
	int		wstatus;
//	char	**environ_bk;

	if (!*args)
		return (0);
//	environ_bk = add_cwd_to_path(*environ_cp);
	cmd = NULL;
	if (args[0])
	{
//		update_env("_", cmd, environ_cp);
		if (args[0][0] && (args[0][0] == '/'
			|| (args[0][0] == '.' && args[0][1] == '/')))
			cmd = ft_strdup(args[0]);
		else
		{
			// TODO Do something sensible when checking that filename must start with ./
			cmd = search_bin(args[0], *environ_cp);
			if (cmd && (count_char(cmd, '/') == 1 && cmd[0] != '/') && (count_char(cmd, '/') == 0
			|| (count_char(cmd, '/') == 1 && (cmd[0] != '.' || cmd[1] != '/'))))
			ft_memdel((void **)&cmd);
		}
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
	else
		ft_printf("minishell: %s: command not found...\n", args[0]);
//	ft_freeda((void ***)&environ_bk, calc_chptr(environ_bk));
//	ft_memdel((void **)&cmd);
	return (0);
}
