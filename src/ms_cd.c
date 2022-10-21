/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:31:31 by jakken            #+#    #+#             */
/*   Updated: 2022/10/21 16:29:09 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int accessibility(char *path)
{
	struct stat	buf;

	if (!stat(path, &buf) && access(path, X_OK))
	{
		ft_printf("minishell: cd: %s: permission denied\n", path);
		return (1);
	}
	if (access(path, F_OK))
	{
		ft_printf("minishell: cd: %s: no such file or directory\n", path);
		return (1);
	}
	return (0);
}

// TODO In linux cwd can be used dynamically, check mac
static int cwd_wrap(char **cwd)
{
	int max_size;

	max_size = 1024;
	*cwd = (char *)ft_memalloc(max_size);
	if (!(*cwd))
		error_exit("Malloc fail\n");
	getcwd(*cwd, max_size);
	if (!(*cwd))
		error_exit("getcwd fail\n");
	return (1);
}

static int chdir_wrap(char *path, char ***environ_cp)
{
	char	*cwd;

	if (!path)
		return (0);
	if (accessibility(path))
		return (0);
	cwd_wrap(&cwd);
	//If path is home dont print cwd after change
	if (chdir(path) == -1
		&& ft_printf("minishell: cd: %s: is not a directory\n", path))
		return (0);
	update_env("OLDPWD", cwd, environ_cp);
	ft_memdel((void **)&cwd);
	cwd_wrap(&cwd);
	update_env("PWD", cwd, environ_cp);
	ft_memdel((void **)&cwd);
	return (1);
}

static int	prev(char **args, char ***environ_cp, char **cwd)
{
	char *path;

	if (ft_equstrlen(args[1], "-"))
	{
		path = search_variable(*environ_cp, "OLDPWD");
		if (!path && ft_printf("minishell: cd: OLDPWD not set\n"))
			return (1);
		if(chdir_wrap(path, environ_cp) && cwd_wrap(cwd))
		{
			ft_memdel((void **)&path);
			ft_printf("%s\n", *cwd);
			ft_memdel((void **)cwd);
		}
		return (1);
	}
	return (0);
}

int	ms_cd(char **args, char ***environ_cp)
{
	char	*cwd;
	char	*path;

	if (!args[1] || (args[1] && ft_equstrlen(args[1], "--")))
	{
		path = search_variable(*environ_cp, "HOME");
		chdir_wrap(path, environ_cp);
		ft_memdel((void **)&path);
		return (0);
	}
	if (prev(args, environ_cp, &cwd))
		return (0);
	else
	{
		chdir_wrap(args[1], environ_cp);
		return (0);
	}
	return (1);
}
