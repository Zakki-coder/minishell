/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/03 17:07:22 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
/* OR make reallocarray */
void	**ft_realloc_darray(void ***d_array, size_t old_size, size_t new_size)
{
	void	**new;
	int		i;

	i = 0;
	if (!d_array || !(*d_array))
		return (NULL);
	new = ft_memalloc(new_size);
	if (!new)
		return (NULL);
	while((*d_array)[i])
	{
		new[i] = (*d_array)[i];
		++i;
	}
	ft_freeda(d_array, old_size);
	return (new);
}

static char *before_quote(char *line)
{
	char	*quote;
	char	*res;

	res = NULL;
	quote = ft_strchr(line, '\'');
	if (quote > line[0])
		res = ft_strndup(line, quote - line[0]);
	return (res);
}

static char **check_for_quotes(char **execs, char *line, int *n_pointers)
{
	char *quote;

	quote = ft_strchr(line, '\'');
	if (quote == line[0])
}

int	calculate_quotes(char *line, char q_type)
{
	int n;

	n = 0;
	while (line)
	{
		if (*line == q_type)
			++n;
	}
	return (n);
}

/* We should validate the ones starting earlier */
void validate_quotes(char *line)
{
	char	*quote;	
	int		quote_n;

	quote = ft_strchr(line, '\'');
	if (!quote)
		quote = ft_strchr(line, '"');
	if (quote)
		quote_n = calculate_quotes(quote, *quote);
	if (quote_n > 0 && quote_n % 2 != 0)
	{
		free (line);
		error_exit("Unclosed quotes\n");
	}
}

char *trim_touching_quotes(char *line)
{
	char	*ret;
	char	q[2];
	
	q = "'\"";
	while (line)
	{
		
	}
}

/* Hello"    "mom. If there is whitespace or start on the left side of opening quote, then just evaluate whats inside on the quotes. 
If on the other hand opening quote is touching some other char than ws, then what comes after until next quote is glued to argument */
char **chop_line(char *line)
{
	char	**res;
	int		pointer_n;

	
}
int	parse_input(char **execs, char *line)
{
	size_t	n_pointers;

	/* For testing space only for 2 */
	n_pointers = 2;
	validate_quotes(line);
	execs = chop_line(line);
	execs = ft_memalloc(sizeof(*execs) * n_pointers);
	execs[0] = before_quote(line);
	check_for_quotes(execs, line, &n_pointers)
}

char **get_input(void)
{
	int		fd;
	char	*line;
	char	**execs;

	get_next_line(STDIN_FILENO, &line);
	parse_input(execs, line);
	execs = ft_strsplit(line, ' ');
	return (execs);
}