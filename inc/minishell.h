/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:38:34 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/01 14:31:31 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H 

#include "../libft/libft.h"
#include <fcntl.h>  //open
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> // DEEEELETTELTELETLTLTL

/* parse */
char **get_input(void);
char **copy_enivornment_var(void);
/* Extra */
char *ft_search_str(char **haystack, char *needle);
/* main stuff */
void loop_eternal(char **environ_cp);
#endif