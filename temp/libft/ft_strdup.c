/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:24:44 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/29 18:48:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*target;
	char	*l_str;

	l_str = (char *)ft_memalloc(ft_strlen(s1) * sizeof(*s1) + 1);
	if (!l_str)
		return (NULL);
	target = l_str;
	while (*s1 != '\0')
		*l_str++ = *s1++;
	*l_str = '\0';
	return (target);
}
