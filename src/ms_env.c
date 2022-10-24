/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:42:33 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 16:54:03 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	execute_flags(char **args, int delimit
	, int flags, char **environ_cp)
{
	int	i;

	i = 1;
	while (args[i] && i < delimit)
	{
		if (flags & ENV_I)
			ft_printf("cleaning environ\n");
		if (!(flags & ENV_I) && ft_equstrlen(args[i], "-u"))
		{
			unset(args[i + 1], &environ_cp);
			if (flags & ENV_V)
				ft_printf("unset:\t%s\n", args[i]);
		}
		++i;
	}
}

static void	execute_flags2(char **args, int delimit, int flags)
{
	int	i;

	i = 0;
	while (args[i] && i < delimit)
	{
		if (ft_equstrlen(args[i], "-C"))
		{
			if (flags & ENV_V)
				ft_printf("chdir:\t%s\n", args[i]);
			if (chdir(args[i + 1]) < 0)
				ft_printf("env: chdir failed\n");
		}
		++i;
	}
}

static char	**clean_environ(char **environ_cp)
{
	char	**env;
	char	*temp;

	temp = search_variable(environ_cp, "PATH");
	if (!temp)
		return (NULL);
	env = ft_memalloc(sizeof(*env) * 3);
	if (!env)
		error_exit("Malloc fail\n");
	env[0] = ft_strjoin("PATH=", temp);
	ft_memdel((void **)&temp);
	return (env);
}

/* At least on linux -i not working beacause of execve:
      	the use of a third  argument  to  the
       main  function  is not specified in POSIX.1; according to
       POSIX.1, the environment should be accessed via  the  ex‐
       ternal variable environ(7).
*/
void	ms_env(char **args, char **environ_cp)
{
	int				i;
	unsigned int	flags;
	char			**environ_bk;

	if (args[1])
	{
		environ_bk = ft_cpynstrarr(environ_cp, calc_chptr(environ_cp));
		environ_cp = environ_bk;
		flags = env_flags(args, environ_cp, &i);
		execute_flags(args, i, flags, environ_cp);
		env_set_var(args, &environ_cp, &i, flags);
		execute_flags2(args, i, flags);
		if (args[i])
		{
			if (!(flags & ENV_I))
				executor(&args[i], &environ_cp);
			else
			{
				environ_cp = clean_environ(environ_cp);
				executor(&args[i], &environ_cp);
			}
			return ;
		}
	}
	print_char_arr(environ_cp);
}
