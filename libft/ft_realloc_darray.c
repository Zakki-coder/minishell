/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_darray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:40:52 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/05 20:47:02 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>//delt

void	**ft_realloc_darray(void ***d_array, size_t old_size, size_t new_size)
{
	void	**new;
	int		i;

	i = 0;
	if (!d_array || !(*d_array))
		return (NULL);
	new = ft_memalloc(new_size);
	if (!new)
		return (NULL);
	while ((*d_array)[i])
	{
		new[i] = ft_strdup((*d_array)[i]);
		++i;
	}
	ft_freeda(d_array, old_size);
	*d_array = new;
	return (new);
}
