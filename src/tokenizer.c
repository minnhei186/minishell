/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:35:53 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 18:08:31 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include "../libft/libft.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
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
	static char *const	operators[] = {\
		">>", "<<", "||", "&&", ";;", "<", ">", "&", ";", "(", ")", "|", "\n"};
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
}

// t_token	*word(t_token *current, char **input_p)
/* 	
	while ((**input_p) && !is_metacharacter(**input_p))
	(*input_p)++;
*/
t_token	*word(char **rest, char *line, t_status *status)
{
	char	*word;
	char	*input_head;

	input_head = line;
	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
			skip_single_quote(&line, status);
		else if (*line == DOUBLE_QUOTE_CHAR)
			skip_double_quote(&line, status);
		else
			line++;
	}
	word = ft_strndup(input_head, line - input_head);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

/*
	(Additional part in Linux)
	If removes this part, the current pointer will not be updated
	to point to the new Token.

	The current pointer will keep pointing to the same token.
	Each new token created (new_current) will not be linked into the list.

	The linked list will not be built correctly, leading to an incomplete
	or empty token list.
	
	(Linuxでの追加部分）
	この部分を削除すると、現在のポインタは新しいトークンを指すように更新されません。

	現在のポインタは同じトークンを指し続けます。
	新しく作成された各トークン（new_current）は
	リストにリンクされません。

	リンクリストは正しく構築されず、トークン・リストが不完全または空になります。
*/
static void	add_token(t_token **current, t_token *new_token)
{
	(*current)->next = new_token;
	*current = new_token;
}

/*
	These codes should be in next to the `else` statement

	current->next = new_current;
	current = new_current;
*/
t_token	*tokenizer(char *input_p, t_status *status)
{
	t_token	*current;
	t_token	*new_current;
	t_token	head;

	head.next = NULL;
	current = &head;
	while (*input_p)
	{
		new_current = NULL;
		if (consume_blank(&input_p, input_p))
			continue ;
		else if (is_metacharacter(*input_p))
			new_current = operator(&input_p, input_p);
		else if (is_word(input_p))
			new_current = word(&input_p, input_p, status);
		else
			tokenize_error("Unexpected Token", &input_p, input_p, status);
		if (new_current)
			add_token(&current, new_current);
	}
	add_token(&current, new_token(NULL, TK_EOF));
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
