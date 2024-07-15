/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:05 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/15 15:43:30 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

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

/* Tokenizer Enumeration */
enum	e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

typedef enum e_token_kind	t_token_kind;

typedef struct s_token		t_token;

struct						s_token
{
	t_token_kind			kind;
	char					*word;
	t_token					*next;
};

t_token	*tokenizer(char *input_p);
int		ft_mlt_process(char *line);

#endif
