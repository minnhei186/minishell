/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:05 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/29 22:54:55 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "error.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

/* Tokenizer Enumeration */
enum	e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

typedef enum e_token_kind	t_token_kind;

/* Struct for Tokenizer */
typedef struct s_token		t_token;

struct						s_token
{
	t_token_kind			kind;
	char					*word;
	t_token					*next;
};

// Environment
extern char					**environ;

/* Tokenizer Utils */
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	operators_cmp(char *str, char *key_op);
bool	is_operator(char *input_p);
bool	is_word(char *s);

/* Error */
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *message);
void	fatal_error(const char *msg);

/* tokenizer.c */
t_token	*new_token(char *word, t_token_kind kind, t_token *current);
t_token	*operator(t_token *current, char **input_p);
t_token	*word(t_token *current, char **input_p);
t_token	*tokenizer(char *input_p);

/* do_command.c */
char	*abs_path_get(void);
char	*check_path(char *abs_path, char *line);
char	*find_path(char *line);
char	**subsequent_argv_recursive(t_token *tok, int nargs, char **argv);
char	**token_to_argv(t_token *tok);

/* do_command_utils.c */
void	ft_do_command(char *line);
int		ft_mlt_process(char *line);

#endif
