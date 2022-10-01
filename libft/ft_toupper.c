/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:11:48 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/30 14:52:40 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int	diff;

	diff = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		return (c - diff);
	return (c);
}
