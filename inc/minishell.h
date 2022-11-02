/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:38:34 by jniemine          #+#    #+#             */
/*   Updated: 2022/11/02 13:52:16 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "env.h"
# include "builtins.h"
# include <sys/stat.h>

# define TOKEN_POINTER_N 1

typedef struct s_token
{
	char	*token;
	char	*value;
}	t_token;

/* parse */
int		get_input(char ***environ_cp);
char	**copy_enivornment_var(void);
void	expand_variables(t_token *args, char **environ_cp);
int		parse_variable(char *usd, char **dst);
void	replace_var_with_value(char **var, char **environ_cp);
void	executor(char **args, char ***environ_cp);
int		expand_tilde(char *tilde, char **dest, char **environ_cp);
t_token	*chop_line(char *line, t_token *args, size_t pointer_n);
/*Execute*/
int		execute_bin(char **args, char ***environ_cp);
void	exe_builtins(char **parsed, char ***environ_cp);
char	*search_bin(char *cmd, char **environ_cp);
char	*search_variable(char **environ_cp, char *var_name);
/* Builtins */
void	ms_echo(char **args);
int		ms_cd(char **args, char ***environ_cp);
int		ms_setenv(char **args, char ***environ_cp);
int		ms_unsetenv(char **args, char ***environ_cp);
int		ms_exit(char **args, char ***environ_cp);
void	ms_env(char **args, char **environ_cp);
/* Env */
int		update_env(const char *name, const char *value, char ***environ_cp);
int		unset(char *name, char ***environ_cp);
void	env_set_var(char **args, char ***environ_cp, int *i, int flags);
int		env_flags(char **args, char **environ_cp, int *i);
/*Error*/
void	error_exit(char *msg);
/* Extra */
char	*ft_search_str(char **haystack, char *needle);
size_t	calc_chptr(char **arr);
void	print_char_arr(char **arr);
void	free_tokens(t_token **args);
int		cwd_wrap(char **cwd);
char	**ft_cpynstrarr(char **sarr, int n);
/* main stuff */
void	loop_eternal(char ***environ_cp);
/* Is functions */
int		is_ws(char c);
int		is_quote(char c);
int		is_nl(char c);
int		is_varchr(char c);
#endif