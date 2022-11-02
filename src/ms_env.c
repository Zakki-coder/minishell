/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:42:33 by jakken            #+#    #+#             */
/*   Updated: 2022/11/02 14:09:15 by jniemine         ###   ########.fr       */
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

static char	**clean_environ(char ***environ_bk)
{
	char	**env;
	char	*temp;

	temp = search_variable(*environ_bk, "PATH");
	if (!temp)
		return (NULL);
	ft_freeda((void ***)environ_bk, calc_chptr(*environ_bk));
	env = ft_memalloc(sizeof(*env) * 3);
	if (!env)
		error_exit("Malloc fail\n");
	env[0] = ft_strjoin("PATH=", temp);
	ft_memdel((void **)&temp);
	return (env);
}

static void	choose_environ(char **args, char ***environ_bk, int flags, int i)
{
	if (!(flags & ENV_I))
		executor(&args[i], environ_bk);
	else
	{
		*environ_bk = clean_environ(environ_bk);
		executor(&args[i], environ_bk);
	}
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

	environ_bk = ft_cpynstrarr(environ_cp, calc_chptr(environ_cp));
	if (args[1])
	{
		flags = env_flags(args, environ_bk, &i);
		execute_flags(args, i, flags, environ_bk);
		env_set_var(args, &environ_bk, &i, flags);
		execute_flags2(args, i, flags);
		if (args[i])
		{
			choose_environ(args, &environ_bk, flags, i);
			ft_freeda((void ***)&(environ_bk), calc_chptr(environ_bk));
			return ;
		}
	}
	print_char_arr(environ_bk);
	ft_freeda((void ***)&(environ_bk), calc_chptr(environ_bk));
}
