/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:38:34 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/11 19:07:38 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <fcntl.h>  //open
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> // DEEEELETTELTELETLTLTL

#define TOKEN_POINTER_N 1

typedef struct s_token
{
	char *token;
	char *value;
}	t_token;

/* parse */
t_token *get_input(char **environ_cp);
char **copy_enivornment_var(void);
void	expand_variables(t_token *args, char **environ_cp);
int	parse_variable(char *usd, char **dst);
void replace_var_with_value(char **var, char **environ_cp);
/*Error*/
void	error_exit(char *msg);
/* Extra */
char *ft_search_str(char **haystack, char *needle);
int	is_quote(char c);
/* main stuff */
void loop_eternal(char **environ_cp);
/*for tests */
t_token *chop_line(char *line, t_token *args, size_t size);
#endif