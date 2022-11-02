/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:47:47 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:38:05 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	loop_eternal(char ***environ_cp)
{
	const char	*prompt = ":-) ";

	while (1)
	{
		ft_putstr(prompt);
		get_input(environ_cp);
	}
}
