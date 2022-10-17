/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:36:02 by jakken            #+#    #+#             */
/*   Updated: 2022/10/17 18:25:02 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_name (char *var)
{
	if (ft_isdigit(var[0]))
		return (0);
	while (*var)
	{
		if (!is_varchr(*var))
			return (0);
		++var;
	}
	return (1);
}

int	ft_str_and_len_equ(char *s1, char *s2)
{
	return(ft_strequ(s1, s2) && ft_strlen(s1) == ft_strlen(s2));
}

//setenv doesn't check the correctness of var name, at least on linux
int	ms_setenv(const char *name, const char *value, char **environ_cp)
{
	int		i;
	char	*name_value;

	name_value = ft_memalloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!name_value)
		error_exit("Malloc fail\n");
	ft_strcpy(name_value, name);
	ft_strcat(name_value, "=");
	while (environ_cp[i] && !ft_strequ(environ_cp[i], name_value))
		++i;
	ft_strcat(name_value, value);
	if (environ_cp[i])
	{
		free (environ_cp[i]);
		environ_cp[i] = name_value;
	}
	else
	{
		i = calc_chptr(environ_cp);
		ft_realloc_darray((void ***)&environ_cp, i, sizeof(*environ_cp) * (i + 1));
		environ_cp[i] = name_value;
	}
	return (0);
}

/* Size of the copy is going to be n pointers*/
/* Does not free the original*/
char	**ft_cpynstrarr(char **sarr, int n)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = (char **)ft_memalloc(sizeof(*cpy) * (n + 1));
	while (sarr[i] && i < n)
	{
		cpy[i] = ft_strdup(sarr[i]);
		++i;
	}
}
// TODO We need setenv so we can change/add NAME=VALUE to environ.
// TODO We need to parse flags, make something universal
// TODO We need unset also for -u flag
// If no command is called after name=value pairs are set, make temporary changes and print temp env
// At least on linux, env doesnt set the correctness of given variable name, so it can be anything
// Test with empty value
// With -i flag unset does nothing
static int env_get_flag(char **args, int i, int flags)
{
	if (ft_str_and_len_equ(args[i], "-v"))
		flags &= ENV_V;
	else if (ft_str_and_len_equ(args[i], "-i"))
		flags &= ENV_I;
	else if (ft_str_and_len_equ(args[i], "-u"))
		flags &= ENV_U;
	else if (ft_str_and_len_equ(args[i], "-C"))
		flags &= ENV_C;
	else
	{
		ft_printf("env: unrecognized option '%s'\n", args[i]);
		return (-1);
	}
	return (flags);
}

static int env_flags_parse(char **args, int delimit)
{
	int	flags;
	int	i;

	flags = 0;
	i = 1;
	while (args[i] && i < delimit)
	{
		if (args[i][0] == '-')
			flags = env_get_flag(args, i, flags);
		++i;
	}
	return (flags);
}


/* Parse all flags before var assignment/command/null */
//TODO should it use builtins also as delimiter, now only binaries are used?
static int env_flags(char **args, char **environ_cp, int *i)
{
	int		delimit;
	char	*cmd;
	int		flags;

	*i = 1;
	delimit = 1;
	cmd = NULL;
	while (args[delimit])
	{
		cmd = search_bin(args[delimit], environ_cp);
		if (cmd || ft_strchr(args[delimit], '='))
		{
			ft_memdel((void **)&cmd);
			break;
		}
		++delimit;
	}
	flags = env_flags_parse(args, delimit);
	*i = delimit;
	return (flags);
}

void	env_set_var(char **args, char **environ_cp, int *i, int flags)
{
	char	**name_val;
	char	*eq;

	while (args[*i])
	{
		name_val = NULL;
		eq = NULL;
		eq = ft_strchr(args[*i], '=');
		if (eq)
			name_val = ft_strsplit(args[*i], '=');
		else
			break ;
		if (name_val[0] && name_val[1])
			ms_setenv(name_val[0], name_val[1], environ_cp);
		else if (name_val[0])
			ms_setenv(name_val[0], "", environ_cp);
		else if (eq)
			ms_setenv("=", "", environ_cp);
		ft_freeda((void ***)&name_val, calc_chptr(name_val));
		if (flags & ENV_V)
			ft_printf("setenv:\t%s\n", environ_cp[calc_chptr(environ_cp)]);
		++(*i);
	}
}

int ms_unsetenv(char *name, char **environ_cp)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (-1);
	var_name = ft_memalloc(ft_strlen(name) + 2);
	if (!var_name)
		error_exit("Malloc fail\n");
	var_name[ft_strlen(name)] = '=';
	while (!ft_strequ(environ_cp[i], var_name))
		++i;
	if (environ_cp[i])
	{
		ft_memdel(environ_cp[i]);
		while (environ_cp[i + 1])
		{
			environ_cp[i] = environ_cp[i + 1];
			++i;
		}
	}
	return (0)
}


static void execute_flags(char **args, int delimit, int flags)
{
	int i;

	i = 1;
	while (args[i] && i < delimit)
	{
		if (flags & ENV_I)
			ft_printf("cleaning environ\n");
		if (!(flags & ENV_I) && ft_str_and_len_equ(args[i], "-u"))
		{
			ms_unsetenv(args[i + 1];
			if (flags & ENV_V)
				ft_printf("unset:\t%s\n", args[i]);
		}
	}
}

static void execute_flags2(char **args, int delimit, int flags)
{
	int i;

	i = 0;
	while (args[i] && i < delimit)
	{
		if (ft_str_and_len_equ(args[i], "-C"))
		{
			if (flags & ENV_V)
				ft_printf("chdir:\t%s\n", args[i]);
			if (chdir(args[i + 1]) < 0)
				ft_printf("env: chdir failed\n");
		}
	}
}

// TODO check whic flags are needed on mac, first check for flags, then execute if there are exes
void	ms_env(char **args, char **environ_cp)
{
	size_t		len;
	int			i;
	char		*cmd;
	unsigned	flags;
	char		**environ_bk;

	len = calc_chptr(args);
	//There can be program name and flags before key value pair, at least
	//First check for flags, then loop all name=value pairs then check for command, of none, print, else do else
	if (len == 1)
		print_char_arr(environ_cp);
	else
	{
		// Env never makes permanent changes????? So use a cpy from the start
		environ_bk = ft_cpynstrarr(environ_cp, calc_chptr(environ_cp));
		environ_cp = environ_bk;
		flags = env_flags(args, environ_cp, &i);
		//execute i/unset
		execute_flags(args, i, flags);
		//setenv
		env_set_var(args, environ_cp, &i, flags);
		//execute chdir `
		execute_flags2(args, i, flags);
		if (flags & ENV_I)
			//Make "Empty" environ
		//If cmd is found execute if verbose, print args starting from i.
		cmd = search_bin(args[i], environ_cp);
		if (cmd)
		{
			ft_memdel((void **)&cmd);
			if (flags & !(flags & ENV_I))
				execute_bin(args[i], environ_cp);
			else
				execute_bin(args[i], environ_bk); //This should be "empty" environ
		}
	}
}

enum builtins {env, echo, setenv};

enum builtins char_to_builtin(char *arg)
{
	unsigned	len;

	len = ft_strlen(arg);
	if (ft_strlen("echo") == len && ft_strequ("echo", arg))
		return (echo);
	else if (ft_strlen("env") == len && ft_strequ("env", arg))
		return (env);
	else if (ft_strlen("setenv") == len && ft_strequ("setenv", arg))
		return (setenv);
	return (-1);
}

// There is nothing in p array index zero at the moment, because env takes two args
void	exe_builtins(char **args, char **environ_cp)
{
	enum builtins cmd;
	void (*p[3])(char **);

	p[1] = ms_echo;
	p[2] = ms_setenv;
	cmd = char_to_builtin(args[0]);
	if (cmd == env)
		ms_env(args, environ_cp);
	else if (cmd >= 0)
		p[cmd](args);
	else
		ft_printf("minishell: %s: command not found...\n", args[0]);
}
