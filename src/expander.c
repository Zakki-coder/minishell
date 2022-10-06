/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/06 21:16:43 by jniemine         ###   ########.fr       */
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

static void	expand_variables(t_token *args)
{
	int		i_arg;
	char	*usd;
	char	*var;

	i_arg = 0;
	while (args[i_arg].value)
	{
		/* If dollar is not inside any quotes */
		if (!is_quote(args[i_arg].value[0]))
		{
			usd = ft_strchr(args[i_arg].value, '$');
			if (usd && ((usd > &args[i_arg].value[0] && *(usd - 1) != '\\')
				|| usd == &args[i_arg].value[0]))
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

char **expander(t_token *args)
{
	expand_variables(args);
	/*FOR COMPILE */
	return (NULL);
}