#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void						fatal_error(const char *msg) __attribute__((noreturn));

void	assert_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

enum						e_token_kind
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

t_token	*new_token(char *word, t_token_kind kind, t_token *current)
{
	t_token	*tok;

	tok = (t_token *)calloc(1, sizeof(t_token));
	if (!tok)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	current->next = tok;
	return (tok);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	return (c && strchr("|&;*() <>\t\n", c));
}

bool	is_word(char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*word(t_token *current, char **input_p)
{
	char	*word;
	char	*input_head;

	input_head = *input_p;
	while ((**input_p) && !is_metacharacter(**input_p))
		(*input_p)++;
	word = strndup(input_head,(*input_p)-input_head);
	if (!word)
		fatal_error("strdup");
	return (new_token(word, TK_WORD, current));
}

t_token	*tokenizer(char *input_p)
{
	t_token	*current;
	t_token	head;

	current = &head;
	while (*input_p)
	{
		while (is_blank(*input_p))
			input_p++;
		//	if (is_op(*input_p))
		//		currnt = operator(currnt, &input_p);
		if (is_word(input_p))
			current = word(current, &input_p);
		else
			assert_error("Unexpected Token");
	}
	new_token(NULL, TK_EOF, current);
	return (head.next);
}

int	main(int argc, char **argv)
{
	t_token	*tok;

	if (argc != 2)
		return (1);
	tok = tokenizer(argv[1]);
	while (tok->word != NULL)
	{
		printf("%s ", tok->word);
		tok = tok->next;
	}
	return (0);
}
