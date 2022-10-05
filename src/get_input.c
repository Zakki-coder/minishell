/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/05 21:00:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_quotes(char *line, char q_type)
{
	int	n;

	n = 0;
	while (line)
	{
		if (*line == q_type)
			++n;
	}
	return (n);
}

void	validate_quotes(char *line)
{
	char	*s_quote;
	char	*w_quote;
	char	*quote;

	while (*line)
	{
		s_quote = ft_strchr(line, '\'');
		w_quote = ft_strchr(line, '"');
		if (!s_quote && !w_quote)
			break ;
		if (!w_quote || (s_quote && s_quote < w_quote))
			quote = s_quote;
		else
			quote = w_quote;
		quote = ft_strchr(quote + 1, *quote);
		if (!quote)
		{
			free (line);
			error_exit("Unclosed quotes\n");
		}
		else
			line = quote;
		++line;
	}
}

int	parse_input(char **args, char *line)
{
	if (!line)
		return (0);
	validate_quotes(line);
	args = (char **)ft_memalloc(sizeof(*args) * (ARG_BUF_SIZE + 1));
	args = chop_line(line, args, ARG_BUF_SIZE + 1);
	//TODO: Evaluate variables then quotes
	expander(args);
	return (-2);
}

char	**get_input(char **environ_cp)
{
	int		fd;
	char	*line;
	char	**execs;

	get_next_line(STDIN_FILENO, &line);
	parse_input(execs, line);
	free(line);
	return (execs);
}
