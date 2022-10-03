/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:35:45 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/01 10:33:29 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void)
{
	char **environ_cp;
	//Handle ENV variables
	environ_cp = copy_enivornment_var();
	loop_eternal(environ_cp);
	//Build loop

}