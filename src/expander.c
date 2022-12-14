/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/29 10:15:17 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	everything_before_usd(char *str, char **dst)
{
	char	*usd;

	usd = ft_strchr(str, '$');
	if (usd)
	{
		*dst = ft_strsub(str, 0, usd - str);
		if (!(*dst))
			error_exit("Malloc fail\n");
	}
	else
		*dst = ft_strsub(str, 0, ft_strlen(str));
	return (ft_strlen(*dst));
}

static void	construct_str(char **dst, char ***splitted_str)
{
	char	*res;
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while ((*splitted_str)[i])
		len += ft_strlen((*splitted_str)[i++]);
	res = ft_memalloc(len + 1);
	if (!res)
		error_exit("Malloc fail\n");
	i = 0;
	while ((*splitted_str)[i])
		ft_strcat(res, (*splitted_str)[i++]);
	free(*dst);
	ft_freeda((void ***)splitted_str, i + 1);
	*dst = res;
}

static void	init_expand_arg(char ***splitted_str, size_t *pointer_n,
	size_t *i_pointer, size_t *i)
{
	*pointer_n = 2;
	*i_pointer = 0;
	*i = 0;
	*splitted_str = (char **)ft_memalloc(sizeof(**splitted_str) * (*pointer_n));
}

/*	Chop into array of pointers*/
static void	expand_arg(char **str, char **environ_cp)
{
	char	**splitted_str;
	size_t	pointer_n;
	size_t	i_pointer;
	size_t	i;

	init_expand_arg(&splitted_str, &pointer_n, &i_pointer, &i);
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += parse_variable(&(*str)[i], &splitted_str[i_pointer]);
			replace_var_with_value(&splitted_str[i_pointer++], environ_cp);
		}
		else if ((*str)[0] == '~')
			i += expand_tilde(&(*str)[i], &splitted_str[i_pointer], environ_cp);
		else
			i += everything_before_usd(&(*str)[i], &splitted_str[i_pointer++]);
		if (i_pointer >= pointer_n - 2)
		{
			splitted_str = (char **)ft_realloc_darray((void ***)&splitted_str,
					pointer_n, pointer_n * 2 * sizeof(*splitted_str));
			pointer_n *= 2;
		}
	}
	construct_str(str, &splitted_str);
}

/*	Inside strong quotes, nothing gets expanded,
	neither will anything which has been backquoted */
void	expand_variables(t_token *args, char **environ_cp)
{
	int		i_arg;

	i_arg = 0;
	while (args[i_arg].value)
	{
		if (!is_quote(args[i_arg].value[0]))
			expand_arg(&args[i_arg].value, environ_cp);
		else if (args[i_arg].value[0] == '"')
			expand_arg(&args[i_arg].value, environ_cp);
		++i_arg;
	}
}
