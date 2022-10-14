/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:36:02 by jakken            #+#    #+#             */
/*   Updated: 2022/10/14 15:16:57 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TODO Greate some builtins then create env maybe arr of pointer to function and enum?
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

int	ms_setenv(const char *name, const char *value, char **environ_cp)
{
	int		i;
	char	*name_value;

	//TODO check that value is legit, ie alpha digit or _ doestn start with digit
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
// TODO We need setenv so we can change/add NAME=VALUE to environ.
// TODO We need to parse flags, make something universal
// TODO We need unset also for -u flag
// If no command is called after name=value pairs are set, make temporary changes and print temp env
void	ms_env(char **args, char **environ_cp)
{
	size_t	len;
	char	*cmd;

	len = calc_chptr(args);
	if (len == 1)
		print_char_arr(environ_cp);
	else if (len > 1)
	{

	}
}

enum builtins {echo, env};

enum builtins char_to_builtin(char *arg)
{
	unsigned	len;

	len = ft_strlen(arg);
	if (ft_strlen("echo") == len && ft_strequ("echo", arg))
		return (echo);
	else if (ft_strlen("env") == len && ft_strequ("env", arg))
		return (env);
	return (-1);
}

void	exe_builtins(char **args, char **environ_cp)
{
	enum builtins cmd;
	void (*p[2])(char **);

	p[0] = ms_echo;
	cmd = char_to_builtin(args[0]);
	if (cmd == env)
		ms_env(args, environ_cp);
	else if (cmd >= 0)
		p[cmd](args);
	else
		ft_printf("minishell: %s: command not found...\n", args[0]);
}
