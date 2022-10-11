/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:22 by jakken            #+#    #+#             */
/*   Updated: 2022/10/11 21:49:26 by jniemine         ###   ########.fr       */
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

void debug_arg_tokens(t_token *args)
{
	while (args->token)
	{
		printf("ID: %s value: %s\n", args->token, args->value);
		++args;
	}
}

void free_tokens(t_token **args)
{
	t_token *deref;

	deref = *args;
	while (deref->token)
	{
		free (deref->token);
		free (deref->value);
		deref->token = NULL;
		deref->value = NULL;
		++deref;
	}
	free (*args);
}

void remove_quotes(t_token *args)
{
	size_t len;

	while (args->token)
	{
		len = ft_strlen(args->token);
		if (is_quote(args->token[0]) && is_quote(args->token[len - 1]))
		{
			args->token[len - 1] = '\0';
			ft_memmove(args->token, &args->token[1], ft_strlen(&args->token[1]));
			args->token[len - 2] = '\0';
		}
		len = ft_strlen(args->value);
		if (is_quote(args->value[0]) && is_quote(args->value[len - 1]))
		{
			args->value[len - 1] = '\0';
			ft_memmove(args->value, &args->value[1], ft_strlen(&args->value[1]));
			args->value[len - 2] = '\0';
		}
		++args;
	}
}

int	parse_input(t_token *args, char *line, char **environ_cp)
{
	if (!line)
		return (0);
	validate_quotes(line);
	args = (t_token *)ft_memalloc(sizeof(*args) * (TOKEN_POINTER_N + 1));
	args = chop_line(line, args, TOKEN_POINTER_N);
//	debug_arg_tokens(args);
	expand_variables(args, environ_cp);
	remove_quotes(args);
	//TODO: also do some norming
//	debug_arg_tokens(args);
	free_tokens(&args);
	return (-2);
}

/* Remember that GNL gets rid of newline */
t_token	*get_input(char **environ_cp)
{
	int		fd;
	char	*line;
	t_token	*execs;

	get_next_line(STDIN_FILENO, &line);
	parse_input(execs, line, environ_cp);
	free(line);
	return (execs);
}
