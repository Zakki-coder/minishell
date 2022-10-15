/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:36:02 by jakken            #+#    #+#             */
/*   Updated: 2022/10/15 15:49:06 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ms_echo(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		++i;
	}
	ft_printf("\n");
}

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
	ft_strcat(name_value, value);
	while (environ_cp[i] && !ft_strequ(environ_cp[i], name))
		++i;
	if (environ_cp[i] && environ_cp[i][ft_strlen(name)] == '=')
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

int	ft_str_and_len_equ(char *s1, char *s2)
{
	return(ft_strequ(s1, s2) && ft_strlen(s1) == ft_strlen(s2));
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
	if (ft_str_and_len_equ(args[i], "-i")
		flags &= ENV_I;
	else if (ft_str_and_len_equ(args[i], "-u")
		flags &= ENV_U;
	else if (ft_str_and_len_equ(args[i], "-C")
		flags &= ENV_U;
	else if (ft_str_and_len_equ(args[i], "-v")
		flags &= ENV_V;
	else
	{
		ft_printf("env: unrecognized option '%s'\n", args[i]);
		return (-1);
	}
	return (1);
}

static int env_flags(char **args)
{
	int	flags;
	int	i;

	flags = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
			flags = env_get_flag(args, i, flags);
		++i;
	}
}

// TODO Use the exe as delimiter, first find v then i then doesnt matter
static int env_flags(char **args)
{
	int i;

	i = 1;
	//While argument starts with - its option, for u c and s next arg is it's arg
	//-v should be checked for first -i second, else dont matter?
	while (args[i])
	{
		if (args[i][0] == '-')
			env_handle_flag(args, i);
	}
}
void	ms_env(char **args, char **environ_cp)
{
	size_t		len;
	char		*cmd;
	char		*eq;
	unsigned	flags;

	len = calc_chptr(args);
	//There can be program name and flags before key value pair, at least
	//First check for flags, then loop all name=value pairs then check for command, of none, print, else do else
	eq = ft_strchr(args[0], '=');
	if (len == 1)
		print_char_arr(environ_cp);
	else if (eq)
	{
		cmd = ft_strsub(arg[0], 0, eq - arg[0]);
		ms_setenv(name, eq + 1, environ_cp);
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
