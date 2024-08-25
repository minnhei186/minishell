/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:31:14 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 18:09:12 by geonwkim         ###   ########.fr       */
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

typedef struct s_node		t_node;
typedef struct s_status		t_status;
typedef struct s_map		t_map;

/* Builtin Commands */
enum	e_cmd
{
	B_EXIT,
	B_EXPORT,
	B_UNKNOWN
};
typedef enum e_cmd		t_cmd;


/* builtin.c */
int		exec_builtin(t_node *node, t_status *last_status, t_map *envmap);
bool	is_builtin(t_node *node);

/* builtin_exit.c */
bool	is_numeric(char *s);
int		builtin_exit(char **argv, t_status *status);

/* builtin_export.c */
void	print_allenv(t_map *envmap);
int		builtin_export(char **argv, t_map *envmap);

#endif
