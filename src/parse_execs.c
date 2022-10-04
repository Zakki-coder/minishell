/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:03:38 by jakken            #+#    #+#             */
/*   Updated: 2022/10/04 14:01:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* "echo" hello || echo "hello" 
With strong quotes '' interpret everything as string, excpet commands.
with weak quotes "" expand variables \ quotes next char.
*/
/*
char **parse_execs(char **execs)
{

}
*/