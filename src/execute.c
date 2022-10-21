/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:18 by jakken            #+#    #+#             */
/*   Updated: 2022/10/21 16:48:52 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Allocates return value */
char	*search_variable(char **environ_cp, char *var_name)
{
	int		i;
	char	*var_value;

	i = 0;
	var_value = NULL;
	while (environ_cp[i]
		&& !ft_strnequ(environ_cp[i], var_name, ft_strlen(var_name)))
		++i;
	if (environ_cp[i] && environ_cp[i][ft_strlen(var_name)] == '=')
	{
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
		if (!var_value)
			error_exit("Malloc fail\n");
	}
	return (var_value);
}

int	ft_memd_w(void **ap)
{
	if (!ap || !(*ap))
		return (1);
	ft_memdel(ap);
	return (1);
}

char	*search_bin(char *cmd, char **environ_cp)
{
	char	**bin_paths;
	char	*temp_path;
	char	*exepath;
	int		i;

	i = 0;
	temp_path = search_variable(environ_cp, "PATH");
	if (temp_path)
		bin_paths = ft_strsplit(temp_path, ':');
	while (ft_memd_w((void **)&temp_path) && bin_paths && bin_paths[i])
	{
		temp_path = ft_strjoin(bin_paths[i], "/");
		exepath = ft_strjoin(temp_path, cmd);
		if (ft_memd_w((void **)&temp_path) && !access(exepath, F_OK)
			&& !access(exepath, X_OK))
		{
			ft_freeda((void ***)&bin_paths, calc_chptr(bin_paths));
			return (exepath);
		}
		else
			ft_memdel((void **)&exepath);
		++i;
	}
	ft_freeda((void ***)&bin_paths, calc_chptr(bin_paths));
	return (NULL);
}

int	execute_bin(char **args, char **environ_cp)
{
	char	*cmd;
	int		id;
	int		wstatus;

	if (!*args)
		return (0);
	cmd = search_bin(args[0], environ_cp);
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
