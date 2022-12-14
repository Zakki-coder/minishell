/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:36:12 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/29 10:44:24 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_freeda(void ***a, size_t row)
{
	unsigned int	i;

	i = 0;
	if (!a)
		return (1);
	while ((*a) && (*a)[i] && i < row)
	{
		free((*a)[i]);
		(*a)[i] = NULL;
		++i;
	}
	free(*a);
	*a = NULL;
	return (1);
}
	/*
	 * Takes the address of double pointer as param a
	 * and number of sub pointers as param row frees all and sets them to NULL
	 * Return 1 so can be used inside condition.
	 */
