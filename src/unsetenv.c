/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:39:24 by jakken            #+#    #+#             */
/*   Updated: 2022/10/21 18:24:58 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_unsetenv(char **args, char ***environ_cp)
{
	int 	i;

	i = 1;
	while (args[i])
	{
		unset(args[i], environ_cp);
		++i;
	}
	return (1);
}