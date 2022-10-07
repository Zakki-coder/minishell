/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:22:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/07 20:47:44 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env(char *var, char **environ)
{

}

int is_underscore(char c)
{
	return (c == '_');
}

char	get_brace_pair(char brace)
{
	char pair;

	pair = '\0';
	if (brace == '(')
		pair = ')';
	else if (brace == '{')
		pair = '}';
	return (pair);
}

/*Should return pointer? */
int	search_matching_brace(char *usd, char brace)
{
	char pair;

	pair = get_brace_pair(brace);
	while (*usd && *usd != '}' && *usd != ')')
		++usd;
	if (*usd != pair)
		return (0);
	return (1);
}

/* Search mathing brace should retunr pointer*/
int	test_validity(char *usd)
{
	char brace;

	if (ft_strequ(usd, "$"))
	{
		if (ft_strequ(usd, "$(") || ft_strequ(usd, "${"))
		{
			brace = *(usd + 1);
			if (!search_matching_brace(usd, brace))
				error_exit ("Incorrect bracing in variable");
			usd += 2;
		}
		else
			usd += 1;
	}
	while (ft_isalnum(*usd) || is_underscore(*usd))
		++usd;
	return (1);
}

/* The name of a variable can contain only letters (a to z or A to Z), numbers ( 0 to 9) or the underscore character ( _). */
char	*parse_dollar(char *usd)
{
	char	*parsed;
	int		i;

	i = 0;
	while (!ft_isalnum(*usd) && !is_underscore(*usd))
		++usd;
	while (usd[i])
	{

	}
}