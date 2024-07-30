/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:05:42 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 23:20:50 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

bool	equal_op(t_token *tok, char *op);
void	append_node(t_node **node, t_node *elm);
void	append_command_element(t_node *command, \
		t_token **rest, t_token *token);

// <simple_command> = <command_element>+
// <command_element> = <word> | <redirection>
// <redirection> = '>' <word>
//               | '<' <word>
//               | '>>' <word>
//               | '<<' <word>
t_node	*parse(t_token *token)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &token, token);
	while (token && !at_eof(token))
		append_command_element(node, &token, token);
	return (node);
}

bool	at_eof(t_token *token)
{
	return (token->kind == TK_EOF);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

t_token	*token_dup(t_token *token)
{
	char	*word;

	word = ft_strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, token->kind));
}

void	append_token(t_token **token, t_token *element)
{
	if (*token == NULL)
	{
		*token = element;
		return ;
	}
	append_token(&(*token)->next, element);
}
