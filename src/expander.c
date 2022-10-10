/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:36:56 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/10 21:49:56 by jniemine         ###   ########.fr       */
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

/*Chop into array of pointers, get_env should dup, so that everything can be freed?
	Then make a string from the array? It could be a slightly faster than reallocing
Else you need to calculate var lengths? Actually you can calculate the length while making the array?*/
static void	weak_quotes_expand(char **str, char **environ_cp)
{
	char	*expanded_str;
	char	*expanded_var;
	char	*res;
	char	*usd;
	char	*temp_str;

	temp_str = *str;
	usd = ft_strchr(temp_str, '$');
	if (!usd)
		return ;
	expanded_str = ft_strsub(temp_str, 0, usd - temp_str);
	while (usd)
	{
		expanded_var = parse_variable(usd);
		res = ft_strjoin(expanded_str, get_env(expanded_var, environ_cp));
		temp_str += ft_strlen
		free (expanded_str);
		free (expanded_var);

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