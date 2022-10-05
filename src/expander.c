/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/05 11:12:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	If $'VAR' try to expand $'VAR' return nothing because not found. Output VAR
	If 'VAR'$ There is no variable name given to $ so you just print $ char. Ouput VAR$
	If $"VAR" output $VAR
	If "VAR"$ output VAR$
*/
static void	expand_variables(char **args)
{
	int		i_arg;
	int 	i_str;
	char	*usd;

	i_arg = 0;
	i_str = 0;
	while (args[i_arg])
	{
		if (args[i_arg][0] != '\'')
		{
			usd = ft_strchr(args[i_arg], '$');
			if (usd && ((usd > args[i_arg][0] && *(usd - 1) != '\\')
				|| usd == args[i_arg][0]))

		}
	}
}
char **expander(char **args)
{

}