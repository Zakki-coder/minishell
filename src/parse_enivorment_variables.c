/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enivorment_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:37:37 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/30 21:24:02 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

extern char **environ;

static int calculate_pointers(void)
{
	char **local_env;
	int i;

	local_env = environ;
	i = 0;
	while(*local_env++)
		++i;	
	return (i);
}

char **copy_enivornment_var(void)
{
	int i;
	int n;
	char **environ_cp;

	i = 0;
	n = calculate_pointers();
	environ_cp = (char **)ft_memalloc(sizeof(*environ_cp) * (n + 1));
	if (!environ_cp)
		exit (-1);
	while (environ[i])
	{
		environ_cp[i] = ft_strdup(environ[i]);
		++i;
	}
	environ_cp[i] = NULL;
	return (environ_cp);
}