/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/05 21:05:54 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	If $'VAR' try to expand $'VAR' return nothing because not found. Output VAR
	If 'VAR'$ There is no variable name given to $ so you just print $ char. Ouput VAR$
	If $"VAR" output $VAR
	If "VAR"$ output VAR$
*/
static void usd_touching_strong_quote(char *usd)
{
	if (*(usd + 1) == '\'')
		ft_memmove(usd, usd + 1, ft_strlen(usd + 1) + 1);
}

static void	expand_variables(char **args)
{
	int		i_arg;
	char	*usd;
	char	*var;

	i_arg = 0;
	while (args[i_arg])
	{
		/* If dollar is not inside any quotes */
		if (!is_quote(args[i_arg][0]))
		{
			usd = ft_strchr(args[i_arg], '$');
			if (usd && ((usd > &args[i_arg][0] && *(usd - 1) != '\\')
				|| usd == &args[i_arg][0]))
			{
				usd_touching_strong_quote(usd);
				//Weak quotes and no quotes both expand variables the same
			}

		}
		//else if weak quote
		//else if strong quote
		++i_arg;
	}
}

char **expander(char **args)
{
	expand_variables(args);
	/*FOR COMPILE */
	return (NULL);
}