/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:35:53 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 01:02:23 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "../libft/libft.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = (t_token *)calloc(1, sizeof(t_token));
	if (!tok)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

// t_token	*operator(t_token *current, char **input_p)
/*
	These codes should be in next to the `else` statement
	current->next = new_current;
	current = new_current;
*/
t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {"||", "&", "&&", \
						";", ";;", "(", ")", "|", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (operators_cmp(line, operators[i]))
		{
			op = ft_strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}

// t_token	*word(t_token *current, char **input_p)
/* 	
	while ((**input_p) && !is_metacharacter(**input_p))
	(*input_p)++;
*/
t_token	*word(char **rest, char *line)
{
	char	*word;
	char	*input_head;

	input_head = line;
	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
			skip_single_quote(&line);
		else if (*line == DOUBLE_QUOTE_CHAR)
			skip_double_quote(&line);
		else
			line++;
	}
	word = strndup(input_head, line - input_head);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

t_token	*tokenizer(char *input_p)
{
	t_token	*current;
	t_token	*new_current;
	t_token	head;
	bool	syntax_error;

	syntax_error = false;
	head.next = NULL;
	current = &head;
	while (*input_p)
	{
		new_current = NULL;
		if (consume_blank(&input_p, input_p))
			continue ;
		else if (is_operator(input_p))
			new_current = operator(&input_p, input_p);
		else if (is_word(input_p))
			new_current = word(&input_p, input_p);
		else
			tokenize_error("Unexpected Token", &input_p, input_p);
		current->next = new_current;
		current = new_current;
	}
	current->next = new_token(NULL, TK_EOF);
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
