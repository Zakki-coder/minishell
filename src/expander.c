/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/11 14:37:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	If $'VAR' try to expand $'VAR' return nothing because not found. Output VAR
	If 'VAR'$ There is no variable name given to $ so you just print $ char. Ouput VAR$
	If $"VAR" output $VAR
	If "VAR"$ output VAR$
*/
static void usd_touching_strong_quote(char *usd)
{
	if (*(usd + 1) == '\'')
		ft_memmove(usd, usd + 1, ft_strlen(usd + 1) + 1);
}

unsigned	calculate_char_n(char *str, char c)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		if (*str == c);
			++res;
		++str;
	}
	return (res);
}

static int everything_before_usd(char *str, char **dst)
{
	char *usd;

	usd = ft_strchr(str, '$');
	if (usd)
	{
		if (usd > str)
			--usd;
		*dst = ft_strsub(str, 0, usd - str);
		if (!(*dst))
			error_exit("Malloc fail\n");
	}
	else
		*dst = strsub(str, 0, ft_strlen(str));
	return (ft_strlen(*dst));
}

/*	Chop into array of pointers, get_env should dup, so that everything can be freed?
	Then make a string from the array? It could be a slightly faster than reallocing
	Else you need to calculate var lengths? Actually you can calculate the length while making the array?*/
static void	weak_quotes_expand(char **str, char **environ_cp)
{
	char	**splitted_str;
	size_t	pointer_n;
	size_t	i_pointer;
	size_t	i;

	pointer_n = 10;
	i_pointer = 0;
	i = 0;
	splitted_str = (char **)ft_memalloc(sizeof(*str) * pointer_n);
	while ((*str)[i])
	{
		i = everything_before_usd(&(*str)[i], &splitted_str[i_pointer++]);
		if ((*str)[i] == '$')
		{
			i = parse_variable(&(*str)[i], &splitted_str[i_pointer]);
			get_env(&splitted_str[i_pointer++], environ_cp);
		}
	}
}

/* Inside strong quotes, nothing gets expanded, neither will anything which has been backquoted */
static void	expand_variables(t_token *args, char **environ_cp)
{
	int		i_arg;
	char	*usd;
	char	*var;

	i_arg = 0;
	while (args[i_arg].value)
	{
		/* If dollar is not inside any quotes */
		if (!is_quote(args[i_arg].value[0]))
		{
			usd = ft_strchr(args[i_arg].value, '$');
			if (usd && ((usd > &args[i_arg].value[0] && *(usd - 1) != '\\')
				|| usd == &args[i_arg].value[0]))
			{
				usd_touching_strong_quote(usd);
				//Weak quotes and no quotes both expand variables the same
				weak_quotes_expand(&args[i_arg].value, usd, environ_cp);

			}

		}
				//else if weak quote
				//else if strong quote
		++i_arg;
	}
}

char **expander(t_token *args, char **environ_cp)
{
	expand_variables(args, environ_cp);
	/*FOR COMPILE */
	return (NULL);
}