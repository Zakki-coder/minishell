/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chop_line_to_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:33:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/07 12:09:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	track_used_space(t_token **args, size_t current_pointer_n, size_t *max_pointer_n)
{
	size_t	new_size;
	size_t	growth;
	t_token	*new_args;
	size_t	i;

	growth = 2;
	i = 0;
	if (current_pointer_n >= *max_pointer_n)
	{
		new_size = sizeof(**args) * ((*max_pointer_n) + ((*max_pointer_n) * growth));
		new_args = (t_token *)ft_memalloc(new_size);
		while (i <= current_pointer_n)
		{
			new_args[i] = (*args)[i];
			++i;
		}
		*max_pointer_n = (*max_pointer_n) * growth;
		free(*args);
		*args = new_args;
	}
}

int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int is_nl(char c)
{
	return (c == '\n' || c == ';');
}

/* exceptions are [NOTWS]["] and ["][NOTWS] and [\][WS] */
char	*find_argument(char **line)
{
	int		i;
	char	quote;
	char	*ret;

	i = 0;
	quote = 0;
	while ((*line)[i] && !is_ws((*line)[i]) && !is_nl((*line)[i]))
	{
		while (!is_quote((*line)[i]) && !is_ws((*line)[i]) && (*line)[i])
			++i;
		if (is_ws((*line)[i] && i > 0 && (*line)[i] && (*line)[i - 1] == '\\' && ++i))
			continue ;
		if (is_quote((*line)[i]) && ((i > 0 && !is_ws((*line)[i - 1]))
			|| i == 0))
		{
			quote = (*line)[i++];
			while ((*line)[i] != quote && (*line)[i] != '\0')
				++i;
			if ((*line)[i])
				++i;
		}
	}
	if ((*line)[i] == '\n' || (*line)[i] == ';')
		i = 1;
	ret = ft_strndup((*line), i);
	if (!ret)
		error_exit("Malloc fail");
	(*line) += i;
	return (ret);
}

t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	size_t	i_args;
	char	*argument;

	i_args = 0;
	while (is_ws(*line))
		++line;
	while (*line)
	{
		if (i_args == 0)
			args[i_args].token = find_argument(&line);
		else
		{
			argument = find_argument(&line);
			if (ft_strequ(argument, "\n") || ft_strequ(argument, ";"))
				args[i_args].token = ft_strdup("NEWLINE");
			else
				args[i_args].token = ft_strdup("WORD");
		}
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (is_ws(*line))
			++line;
	}
	return (args);
}
