/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:18 by jakken            #+#    #+#             */
/*   Updated: 2022/10/12 18:50:50 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_variable(char **environ_cp, char *var_name)
{
	int		i;
	char	*var_value;

	i = 0;
	var_value = NULL;
	while (environ_cp[i]
		&& !ft_strnequ(environ_cp[i], *var_name, ft_strlen(*var_name)))
		++i;
	if (environ_cp[i] && environ_cp[i][ft_strlen(*var_name)] == '=')
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
	if (!var_value)
		error_exit("Malloc fail\n");
	return (var_value);
}

char	*search_bin(char *cmd, char **environ_cp)
{
	char	*env_path;
	char	**bin_paths;
	char	*exepath;

	env_path = searhc_variable(environ_cp, "PATH");	
	if (env_path)
		bin_paths = ft_strsplit(env_path, ':');
	while (bin_paths)	
	{
		exepath = ft_strjoin(*bin_paths, cmd);
		if (access(exepath, F_OK) && access(exepath, X_OK))
		{
			//free bin paths
			//return exepath
		}
		++bin_paths;
	}
}

void	execute(char **args, char **environ_cp)
{
	char	*cmd;
	int		id;

	cmd = search_variable(environ_cp, args[0]);
	if (cmd)
	{

	}
}