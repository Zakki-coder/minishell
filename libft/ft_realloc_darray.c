/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_darray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:40:52 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/24 17:08:27 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Pointer_n is the number of already allocated pointers,
	new_size is the size to be allocated */
void	**ft_realloc_darray(void ***d_array, size_t pointer_n, size_t new_size)
{
	void	**new;
	int		i;

	i = pointer_n;
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
	ft_freeda(d_array, pointer_n);
	*d_array = new;
	return (new);
}
