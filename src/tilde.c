/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:26:41 by jakken            #+#    #+#             */
/*   Updated: 2022/10/28 12:08:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	old_pwd(char *tilde, char **dest, char **environ_cp)
{
	char	*temp;

	temp = NULL;
	temp = search_variable(environ_cp, "OLDPWD");
	if (temp)
	{
		if (tilde[1] == '/')
			*dest = ft_strjoin(temp, &tilde[1]);
		else
			*dest = ft_strdup(temp);
	}
	ft_memdel((void **)&temp);
}

static void	pwd(char *tilde, char **dest, char **environ_cp)
{
	char	*temp;

	temp = NULL;
	temp = search_variable(environ_cp, "PWD");
	if (temp)
	{
		if (tilde[1] == '/')
			*dest = ft_strjoin(temp, &tilde[1]);
		else
			*dest = ft_strdup(temp);
	}
	ft_memdel((void **)&temp);
}

int	expand_tilde(char *tilde, char **dest, char **environ_cp)
{
	char	*temp;

	if (tilde[1] == '/' || tilde[1] == '\0')
	{
		temp = search_variable(environ_cp, "HOME");
		if (!temp)
			return (ft_strlen(tilde));
		else
		{
			if (tilde[1] == '/')
				*dest = ft_strjoin(temp, &tilde[1]);
			else
				*dest = ft_strdup(temp);
		}
		ft_memdel((void **)&temp);
	}
	else if (tilde[1] == '-' && (tilde[2] == '\0'
			|| tilde[2] == '/'))
		old_pwd(tilde, dest, environ_cp);
	else if (tilde[1] == '+' && (tilde[2] == '/'
			|| tilde[2] == '\0'))
		pwd(tilde, dest, environ_cp);
	else
		*dest = ft_strdup(tilde);
	return (ft_strlen(tilde));
}
