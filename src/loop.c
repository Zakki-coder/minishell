/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:47:47 by jakken            #+#    #+#             */
/*   Updated: 2022/10/03 12:04:25 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_search_str(char **haystack, char *needle)
{
	if (!needle || !haystack || !(*haystack))
		return (NULL);
	while (*haystack)
	{
		if (ft_strnequ(*haystack, needle, ft_strlen(needle)))
			return (*haystack);
		++haystack;
	}
	return (NULL);
}

/* Not sure if there even is env var PS1 in mac */
static char *get_prompt(char **environ_cp)
{
	char *prompt;

	prompt = ft_search_str(environ_cp, "PS1");
	if (prompt)
		return (prompt);
	else
		prompt = ft_strdup("$ ");
	return (prompt);
}

void loop_eternal(char **environ_cp)
{
	int		signal;
	char	*prompt;
	char	**execs;

	signal = 1;
	prompt = get_prompt(environ_cp);
	while(signal)
	{
		ft_putstr(prompt);
		execs = get_input();
	}
}
