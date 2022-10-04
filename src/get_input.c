/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/04 15:55:18 by jniemine         ###   ########.fr       */
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

void validate_quotes(char *line)
{
	char	*s_quote;	
	char	*w_quote;	
	int		quote_n;

	s_quote = ft_strchr(line, '\'');
	w_quote = ft_strchr(line, '"');
	if (!s_quote && !w_quote)
		return ;
	if (s_quote < w_quote)
		quote_n = calculate_quotes(s_quote, *s_quote);
	else
		quote_n = calculate_quotes(w_quote, *w_quote);
	if (quote_n > 0 && quote_n % 2 != 0)
	{
		free (line);
		error_exit("Unclosed quotes\n");
	}
}

int is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
			|| c == '\f' || c == '\r');
}

int is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char *first_quote(char *line)
{
	char *s_quote;
	char *w_quote;

	s_quote = ft_strchr(line, '\'');
	w_quote = ft_strchr(line, '"');
	if (s_quote && w_quote)
	{
		if (s_quote < w_quote)
			return (s_quote);
		else
			return (w_quote);
	}
	else if (s_quote)
		return (s_quote);
	return (w_quote);
}

char *find_argument(char **line)
{
	int		i;
	char	quote;
	char	*ret;

	i = 0;
	quote = 0;
	while ((*line)[i] && !is_ws((*line)[i]))
	{
		while(!is_quote((*line)[i]) && !is_ws((*line)[i]) && (*line)[i])
			++i;
		if (is_quote((*line)[i]) && ((i > 0 && !is_ws((*line)[i - 1]))
			|| i == 0))
		{
			quote = (*line)[i];
			while ((*line)[i] != quote && (*line)[i] != '\0')
				++i;
			if ((*line)[i])
				++i;
		}
	}
	ret = ft_strndup((*line), i);
	(*line) += i;
	return (ret);
}

void	track_used_space(char ***args, size_t used_space, size_t *size)
{
	int new_size;

	if (used_space >= *size) 
	{
		new_size = *size + ((*size) * 2);
		*args = (char **)ft_realloc_darray((void ***)args, *size, new_size);
		*size = new_size;
	}
}
/* Hello"    "mom. If there is whitespace or start on the left side of opening quote, then just evaluate whats inside on the quotes. 
If on the other hand opening quote is touching some other char than ws, then what comes after until next quote is glued to argument */
char **chop_line(char *line, char **args, size_t size)
{
	size_t	i_args;

	//Copy until whitespace or quote.
	//If quote is touching to some other char than ws, then it is joined
	//First we split the arguments without doing anything to quotes, then we expand the quotes
	i_args = 0;
	while (*line)	
	{
		while (is_ws(*line))
			++line;
		args[i_args] = find_argument(&line);
		printf("ARG: |%s|\n", args[i_args]);
		++i_args;
		//Check for realloc i_args vs size
		track_used_space(&args, i_args, &size);
	}
	/*Just to compile */
	return args;
}

int	parse_input(char **execs, char *line)
{
	size_t	n_pointers;
	
	/* For testing space only for 2 */
	validate_quotes(line);
	n_pointers = 1;
	execs = (char **)ft_memalloc(sizeof(*execs) * n_pointers);
	chop_line(line, execs, n_pointers);
	/*For compile*/
	return -2;
}

char **get_input(void)
{
	int		fd;
	char	*line;
	char	**execs;

	get_next_line(STDIN_FILENO, &line);
	parse_input(execs, line);
	return (execs);
}