/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:31:14 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/31 18:13:39 by geonwkim         ###   ########.fr       */
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
typedef enum e_cmd		t_cmd;

/* builtin.c */
// original
// int		exec_builtin(t_node *node, t_status *last_status, t_map *envmap);
int		exec_builtin(t_node *node, t_status *p_status);
bool	is_builtin(t_node *node);

/* builtin_exit.c */
bool	is_numeric(char *s);
int		builtin_exit(char **argv, t_status *status);

/* builtin_export.c */
void	print_allenv(t_map *envmap);
int		builtin_export(char **argv, t_map *envmap);

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
