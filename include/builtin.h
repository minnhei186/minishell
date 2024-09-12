/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:31:14 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/13 00:19:24 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"minishell.h"
# include	"error.h"
# include	"last_status.h"

# include	<unistd.h>
# include	<error.h>
// To recognize bool type when it use C99 In VSCode
# include	<stdbool.h>

# include	<limits.h>
# include	<sys/stat.h>

# include	<stdio.h>
# include	<string.h>

typedef struct s_node		t_node;
typedef struct s_status		t_status;
typedef struct s_map		t_map;

/* Builtin Commands */
enum	e_cmd
{
	B_EXIT,
	B_EXPORT,
	B_UNSET,
	B_CD,
	B_ECHO,
	B_PWD,
	B_UNKNOWN
};

typedef enum e_cmd			t_cmd;

/* builtin.c */
// original
// int		exec_builtin(t_node *node, t_status *last_status, t_map *envmap);
int		exec_builtin(t_node *node, t_status *p_status);
bool	is_builtin(t_node *node);

/* builtin_exit.c */
bool	is_numeric(char *s);
int		builtin_exit(char **argv, t_status *status);

/* builtin_export.c */
void	print_env_for_name(t_map *envmap, char *env_name);
void	print_allenv(t_map *envmap);
int		builtin_export(char **argv, t_map *envmap);

/* export_handler.c */
int		handle_export_append(t_map *envmap, char *arg);
int		handle_export_no_equals(char *arg, t_map *envmap);
int		handle_append(t_map *envmap, const char *arg);

/* expotr_get_variable.c */
char	*get_var_name(const char *arg, const char *plus_equal_sign);
char	*get_new_value(const char *plus_equal_sign);
char	*concat_values(const char *current_value, const char *new_value);
int		store_final_value(t_map *envmap, const char *var_name, \
		const char *joined_value);
int		validate_and_free(char *var_name, char *new_value);

/* builtin_unset.c */
int		builtin_unset(char **argv, t_map *envmap);
// int		builtin_unset(char **argv, t_status *last_status);

/* builtin_env.c */
int		builtin_env(char **argv, t_map *envmap);

/* builtin_cd.c */
bool	consume_path(char **rest, char *path, char *element);
void	delete_last_element(char *path);
void	append_path_element(char *dst, char **rest, char *src);
char	*resolve_pwd(char *oldpwd, char *path);
int		builtin_cd(char **argv, t_map *envmap);

/* builtin_echo.c */
int		builtin_echo(char **argv);

/* builtin_pwd.c */
int		builtin_pwd(char **argv);

#endif
