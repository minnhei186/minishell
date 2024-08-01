#include "readline.h"

void						fatal_error(const char *msg) __attribute__((noreturn));

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

bool	operators_cmp(char *str, char *key_op)
{
	return (memcmp(str,key_op,strlen(key_op))==0);
}

bool	is_operator(char *input_p)
{
	size_t	i;

	static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|",
		"\n"};
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (operators_cmp(input_p, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token	*operator(t_token *current, char **input_p)
{
	size_t	i;
	char	*op;

	static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|",
		"\n"};
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (operators_cmp(*input_p, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*input_p = *input_p + strlen(op);
			return (new_token(op, TK_OP, current));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return NULL;
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
	word = strndup(input_head, (*input_p) - input_head);
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
		if (is_operator(input_p))
			current = operator(current, &input_p);
		else if(is_word(input_p))
			current = word(current, &input_p);
		else
			assert_error("Unexpected Token");
	}
	new_token(NULL, TK_EOF, current);
	return (head.next);
}

////文字列（終端あり）の比較ではなく
//int	main(int argc, char **argv)
//{
//	t_token	*tok;
//
//	if (argc != 2)
//		return (1);
//	tok = tokenizer(argv[1]);
//	while (tok->word != NULL)
//	{
//		printf("%s ", tok->word);
//		tok = tok->next;
//	}
//	return (0);
//}
