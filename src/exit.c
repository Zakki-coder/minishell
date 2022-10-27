/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:57:44 by jakken            #+#    #+#             */
/*   Updated: 2022/10/27 17:42:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_exit(char **args, char ***environ_cp)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	ft_freeda((void ***)&args, calc_chptr(args));
	ft_freeda((void ***)environ_cp, calc_chptr(*environ_cp));
	exit (status);
}
