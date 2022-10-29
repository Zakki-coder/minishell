/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:42:12 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/29 10:20:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	calc_chptr(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

void	free_tokens(t_token **args)
{
	t_token	*deref;

	deref = *args;
	while (deref->token)
	{
		free (deref->token);
		free (deref->value);
		deref->token = NULL;
		deref->value = NULL;
		++deref;
	}
	free (*args);
}

void	print_char_arr(char **arr)
{
	while (*arr)
	{
		ft_printf("%s\n", *arr);
		++arr;
	}
}
