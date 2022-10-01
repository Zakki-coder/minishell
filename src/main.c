/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:35:45 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/30 21:27:35 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *ft_search_str(char **haystack, char *needle)
{
	while (*haystack)
	{
		if (ft_strequ(*haystack, needle))
			return (*haystack);
		++haystack;
	}
	return (NULL);
}

/*
static void print_prompt(char **environ_cp)
{
	
}
*/

static void loop_eternal(char **environ_cp)
{
	int signal;

	signal = 1;
	while(signal)
	{
		//print_prompt();
	}

}

int main(void)
{
	char **environ_cp;
	//Handle ENV variables
	environ_cp = copy_enivornment_var();
	loop_eternal(environ_cp);
	//Build loop

}