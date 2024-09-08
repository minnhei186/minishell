/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:15:48 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/08 21:51:16 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include	"minishell.h"
# include	"last_status.h"
# include	"hashmap.h"
# include	"../libft/libft.h"
# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define ERROR_PREFIX "minishell: "
# include <unistd.h>
# include <stdio.h>

typedef struct s_status		t_status;
typedef struct s_token		t_token;
typedef struct s_item		t_item;

/* 
	error_env_pipe.c
	-> Handle with the pipe error that related to ENV, UNSET and PATH
*/
void	handle_exec_error(char *cmd, char *path);
void	print_env_item(t_item *cur);

/* error_utils.c */
void	perror_prefix(void);
void	todo(const char *msg) __attribute__((noreturn));
void	xperror(const char *l);
void	builtin_error(const char *func, const char *name, const char *err);

/* error.c */
void	assert_error(const char *msg) __attribute__((noreturn));
void	fatal_error(const char *msg) __attribute__((noreturn));
void	error_exit(const char *l, \
		const char *msg, int status) __attribute__((noreturn));
void	tokenize_error(const char *l, char **rest, char *line, \
	t_status *status);
void	parse_error(t_token **rest, t_token *token);
// void	parse_error(const char *l, t_token **rest, t_token *token,
// 	t_status *status);

#endif
