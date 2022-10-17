/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:51:56 by jakken            #+#    #+#             */
/*   Updated: 2022/10/17 17:55:57 by jakken           ###   ########.fr       */
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

void	ms_cd(char **args, char **environ_cp)
{
	int i;

	i = 1;
	//Get homepath
	//parse flags
}