/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:31:14 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/18 20:06:20 by geonwkim         ###   ########.fr       */
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

/* builtin.c */
int		exec_builtin(t_node *node);
bool	is_builtin(t_node *node);

/* builtin_exit.c */
bool	is_numeric(char *s);
int		builtin_exit(char **argv);

#endif
