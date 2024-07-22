/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:04:25 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/22 23:24:06 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "error.h"
# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
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

enum	e_node_kind
{
	ND_SIMPLE_CMD,
};

typedef enum e_node_kind	t_node_kind;

/* Struct for Tokenizer */
typedef struct s_token		t_token;

struct						s_token
{
	t_token_kind			kind;
	char					*word;
	t_token					*next;
};

/* Struct for Node */
typedef struct s_node		t_node;

struct						s_node
{
	t_token					*args;
	t_node_kind				kind;
	t_node					*next;
};

// Environment
extern char					**environ;

/* Quotes */
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

/* Tokenizer Quotes */
void	skip_single_quote(char **line);
void	skip_double_quote(char **line);

/* Tokenizer Utils */
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	operators_cmp(char *str, char *key_op);
bool	is_operator(char *input_p);
bool	is_word(char *s);
bool	consume_blank(char **rest, char *line);

/* Error */
// void	fatal_error(const char *msg) __attribute__((noreturn));
// void	assert_error(const char *message);
// void	fatal_error(const char *msg);

/* tokenizer.c */
// t_token	*new_token(char *word, t_token_kind kind, t_token *current);
t_token	*new_token(char *word, t_token_kind kind);
// t_token	*operator(t_token *current, char **input_p);
t_token	*operator(char **rest, char *line);
// t_token	*word(t_token *current, char **input_p);
t_token	*word(char **rest, char *line);
t_token	*tokenizer(char *input_p);

/* destructor.c */
void	free_node(t_node *node);
void	free_token(t_token *token);
void	free_argv(char **argv);

/* do_command.c */
char	*abs_path_get(void);
char	*check_path(char *abs_path, const char *line);
char	*find_path(const char *line);
char	**subsequent_argv_recursive(t_token *tok, int nargs, char **argv);
char	**token_to_argv(t_token *tok);

/* do_command_utils.c */
// void	ft_do_command(char *line);
// int		ft_mlt_process(char *line);

/* expand.c */
void	append_char(char **s, char c);
void	remove_quote(t_token *token);
void	expand_quote_removal(t_node *node);
void	expand(t_node *token);

/* expand_quote.c */
void	remove_single_quote(char **dst, char **rest, char *p);
void	remove_double_quote(char **dst, char **rest, char *p);

/* parse.c */
t_node	*parse(t_token *token);
bool	at_eof(t_token *token);
t_node	*new_node(t_node_kind kind);
t_token	*token_dup(t_token *token);
void	append_token(t_token **tokens, t_token *token);

#endif
