/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:04:25 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/28 21:55:17 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "hashmap.h"
# include "builtin.h"
# include "last_status.h"
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
typedef struct s_token		t_token;
enum	e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind	t_token_kind;

/* Struct for Tokenizer */
struct						s_token
{
	t_token_kind			kind;
	char					*word;
	t_token					*next;
};

enum	e_node_kind
{
	ND_PIPE_LINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC
};
typedef enum e_node_kind	t_node_kind;

/* 
	Struct for Node
	CMD
	- args (command): "echo hello 1 > out"
	- redirects: redirection

	Redirecting output example
	- target_fd: 1
	- delimiter: recognize and delimite the character
	- file_name: "out"
	- file_fd: open("out")
	- stashed_target_fd: dup(target_fd)

	Pipe-Line
	- in_pipe[2]
	- out_pipe[2]
	- cmd
*/
typedef struct s_node		t_node;
struct						s_node
{
	t_token					*args;
	t_node					*redirects;
	t_token					*file_name;
	t_token					*delimiter;
	bool					is_deli_unquoted;
	t_node_kind				kind;
	t_node					*next;
	int						target_fd;
	int						file_fd;
	int						stashed_target_fd;
	int						in_pipe[2];
	int						out_pipe[2];
	t_node					*cmd;
};

typedef struct s_map		t_map;

/* 
	Struct for Status
	Last Status
	- 
 */
typedef struct s_status		t_status;
struct						s_status
{
	int						last_status;
	bool					syntax_error;
	t_map					*env_map;
};

# define ERROR_PARSE 258

// Environment
// extern int						g_last_status;
// extern char						**environ;
// extern bool						g_syntax_error;
extern bool						g_readline_interrupted;
// Able to use this only
extern volatile sig_atomic_t	g_sig;

/* Read Pipe */
// int		exec(t_node *node);
// original exec
// int		exec(t_node *node, t_map *envmap, t_status *last_status);
int		exec(t_node *node, t_status *last_status);
int		wait_pipeline(pid_t last_pid);
// pid_t	exec_pipeline(t_node *node);
// original exec_pipeline
// pid_t	exec_pipeline(t_node *node, t_map *envmap, t_status *status);
pid_t	exec_pipeline(t_node *node, t_status *status);
// original interpreter
//  void	interpreter(char *line, int *state_loca, t_map *envmap,
// 	t_status *status);
void	interpreter(char *line, int *state_loca, t_status *status);

/* Quotes */
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

/* Tokenizer Quotes */
void	skip_single_quote(char **line, t_status *status);
void	skip_double_quote(char **line, t_status *status);

/* Tokenizer Utils */
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	operators_cmp(char *str, char *key_op);
bool	is_word(char *s);
bool	consume_blank(char **rest, char *line);

/* Tokenizer Redirection */
// bool	is_redirection_operator(const char *s);

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
t_token	*word(char **rest, char *line, t_status *status);
t_token	*tokenizer(char *input_p, t_status *status);

/* destructor.c */
void	free_node(t_node *node);
void	free_token(t_token *token);
void	free_argv(char **argv);

/* do_command.c */
char	*abs_path_get(t_status *p_status);
char	*check_path(char *abs_path, const char *line);
char	*find_path(const char *line, t_status *p_status);
char	**subsequent_argv_recursive(t_token *token, int nargs, char **argv);
char	**token_to_argv(t_token *tok);

/* do_command_utils.c */
// void	ft_do_command(char *line);
// int		ft_mlt_process(char *line);

/* expand.c */
void	append_char(char **s, char c);
void	remove_quote(t_token *token);
void	expand_quote_removal(t_node *node);
void	expand(t_node *token, t_status *status);

/* expand_utils.c */
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_variable(char *s);
void	expand_variable_str(char **dest, char **rest, char *p, \
	t_status *p_status);
void	expand_variable_token(t_token *token, t_status *status);

/* expand_quote.c */
void	remove_single_quote(char **dest, char **rest, char *p);
void	remove_double_quote(char **dest, char **rest, char *p);
void	append_single_quote(char **dest, char **rest, char *p);
void	append_double_quote(char **dest, char **rest, char *p, \
	t_status *status);

/* expand_special_parameter.c */
bool	is_special_parameter(char *s);
void	append_num(char **dest, unsigned int num);
// void	expand_special_parameter_str(
// 	char **dest, char **rest, char *p, unsigned int *last_status);
void	expand_special_parameter_str(char **dest, char **rest, char *p, \
	t_status *status);
char	*expand_heredoc_line(char *line, t_status *status);

/* parse.c */
t_node	*parse(t_token *token);
bool	at_eof(t_token *token);
t_node	*new_node(t_node_kind kind);
t_token	*token_dup(t_token *token);

/* parse_redirection.c */
bool	equal_op(t_token *tok, char *op);
t_node	*redirect_out(t_token **rest, t_token *token);
t_node	*redirect_in(t_token **rest, t_token *token);
t_node	*redirect_append(t_token **rest, t_token *token);
t_node	*redirect_heredoc(t_token **rest, t_token *token);

/* parse_append.c */
void	append_token(t_token **token, t_token *element);
void	append_command_element(t_node *command, t_token **rest, t_token *token);
void	append_node(t_node **node, t_node *element);

/* parse_pipe.c */
t_node	*pipe_line(t_token **rest, t_token *token);
bool	is_control_operator(t_token *token);
t_node	*simple_command(t_token **rest, t_token *token);

/* redirect.c */
int		stashfd(int fd);
int		read_heredoc(const char *delimiter, bool is_deli_unquoted, \
	t_status *status);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

/* redirect_utils.c */
bool	is_redirect(t_node *node);
int		open_redir_file(t_node *node, t_status *status);

/* pipe.c */
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

/* signal_utils.c */
# define SIG 0

void	handler(int signum);

/* signal.c */
void	reset_sig(int signum);
void	ignore_sig(int signum);
void	setup_sigint(void);
int		check_state(void);
void	setup_signal(void);
void	reset_signal(void);

#endif
