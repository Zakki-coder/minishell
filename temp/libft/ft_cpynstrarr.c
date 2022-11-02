/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpynstrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:46 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 15:37:20 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Size of the copy is going to be n pointers*/
/* Does not free the original*/
char	**ft_cpynstrarr(char **sarr, int n)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = (char **)ft_memalloc(sizeof(*cpy) * (n + 1));
	while (sarr[i] && i < n)
	{
		cpy[i] = ft_strdup(sarr[i]);
		++i;
	}
	return (cpy);
}
