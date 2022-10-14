/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:17:46 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/14 15:16:50 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_nl(char c)
{
	return (c == '\n' || c == ';');
}

int is_varchr(char c)
{
	return (ft_isalnum(c) || c == '_');
}
