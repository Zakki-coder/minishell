/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:26:41 by jakken            #+#    #+#             */
/*   Updated: 2022/10/24 12:03:39 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	old_pwd(char *tilde, char **dest, char **environ_cp)
{
	char	*temp;

	temp = NULL;
	temp = search_variable(environ_cp, "OLDPWD");
	if (!temp)
		ft_printf("minishell: $OLDPWD unset\n");
	else
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
	if (!temp)
		ft_printf("minishell: $OLDPWD unset\n");
	else
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
			ft_printf("minishell: $HOME unset\n");
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
