/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:15:48 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/17 21:53:52 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include	"readline.h"
# define ERROR_TOKENIZE 258
# define ERROR_PREFIX "minishell: "
# include <unistd.h>
# include <stdio.h>

/* error_utils.c */
void	perror_prefix(void);
void	todo(const char *msg) __attribute__((noreturn));

/* error.c */
void	assert_error(const char *msg) __attribute__((noreturn));
void	fatal_error(const char *msg) __attribute__((noreturn));
void	error_exit(const char *l, const char *msg, int status) \
		__attribute__((noreturn));
void	tokenize_error(const char *l, char **rest, char *line);
// void	parse_error(const char *l, t_token **rest, t_token **token);

#endif
