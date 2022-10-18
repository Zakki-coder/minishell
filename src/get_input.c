/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/18 16:36:58 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	validate_quotes(char *line)
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

static void	remove_quotes(t_token *args)
{
	size_t	len;

	while (args->token)
	{
		len = ft_strlen(args->token);
		if (is_quote(args->token[0]) && is_quote(args->token[len - 1]))
		{
			args->token[len - 1] = '\0';
			ft_memmove(args->token, &args->token[1],
				ft_strlen(&args->token[1]));
			args->token[len - 2] = '\0';
		}
		len = ft_strlen(args->value);
		if (is_quote(args->value[0]) && is_quote(args->value[len - 1]))
		{
			args->value[len - 1] = '\0';
			ft_memmove(args->value, &args->value[1],
				ft_strlen(&args->value[1]));
			args->value[len - 2] = '\0';
		}
		++args;
	}
}

static char	**token_to_char(t_token *args)
{
	char	**res;
	size_t	i;

	i = 0;
	while (args[i].token)
		++i;
	res = (char **)ft_memalloc(sizeof(*res) * (i + 1));
	i = 0;
	while (args[i].token)
	{
		res[i] = ft_strdup(args[i].value);
		++i;
	}
	return (res);
}

static char	**parse_input(char *line, char **environ_cp)
{
	char	**parsed;
	t_token	*args;

	if (!line)
		return (0);
	validate_quotes(line);
	args = (t_token *)ft_memalloc(sizeof(*args) * (TOKEN_POINTER_N + 1));
	args = chop_line(line, args, TOKEN_POINTER_N);
	expand_variables(args, environ_cp);
	remove_quotes(args);
	parsed = token_to_char(args);
	free_tokens(&args);
	return (parsed);
}

/* Remember that GNL gets rid of newline */
int get_input(char **environ_cp)
{
	char	*line;
	char	**parsed;
	
	line = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0) //Error handle -1?
		return (1);
	parsed = parse_input(line, environ_cp);
	executor(parsed, environ_cp);
	ft_memdel((void **)&line);
	ft_freeda((void ***)&parsed, calc_chptr(parsed));
	return (1);
}
