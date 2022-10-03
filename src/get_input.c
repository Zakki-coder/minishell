/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/03 13:09:12 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *strong_quote(char *line)
{

}

char	*ft_strndup(char *str, size_t n)
{
	char *res;

	res = ft_memalloc(n + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, str, n);
	res[n] = '\0';
	return (res);
}

/*TODO: function to calculate amount of args, from quote to quote is one argument, if no matching quote, do something */
static char **before_quote(char *line)
{
	char *quote;

	quote = ft_strchr(line, '\'');
	if (quote > line[0])
	{
				
	}
}

static char **check_for_quotes(char *line)
{
	char *quote;

	quote = ft_strchr(line, '\'');
	if (quote == line[0])
}

char **get_input(void)
{
	int		fd;
	char	*line;
	char	**execs;
	int i = 0;

	get_next_line(STDIN_FILENO, &line);
	execs = ft_strsplit(line, ' ');
	return (execs);
}