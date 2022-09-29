/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enivorment_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:37:37 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/29 16:51:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

extern char **environ;

char **copy_enivornment_var(void)
{
	while (*environ)
	{
		printf("Key: %s\n", &(*environ)[0], &(*environ)[1]);
		++environ;
	}
	return (NULL);
}