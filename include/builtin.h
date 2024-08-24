/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:31:14 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/24 22:09:51 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"readline.h"
# include	"error.h"
# include	"last_status.h"

# include	<unistd.h>
# include	<error.h>
// To recognize bool type when it use C99 In VSCode
# include	<stdbool.h>

typedef struct s_node		t_node;
typedef struct s_status		t_status;

/* builtin.c */
int		exec_builtin(t_node *node, t_status *last_status);
bool	is_builtin(t_node *node);

/* builtin_exit.c */
bool	is_numeric(char *s);
int		builtin_exit(char **argv, t_status *status);

#endif
