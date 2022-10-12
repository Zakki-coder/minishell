/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:42:12 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/12 13:43:37 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	calculate_char_pointers(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}