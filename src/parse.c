/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:05:42 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/17 21:49:17 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

t_node	*parse(t_token *token)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (token && !at_eof(token))
	{
		if (token->kind == TK_WORD)
			append_token(&node->args, token_dup(token));
		else
			todo("Implement parser");
		token = token->next;
	}
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
}

t_token	*token_dup(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, token->kind));
}

void	append_token(t_token **tokens, t_token *token)
{
	if (*toknes == NULL)
	{
		*tokens = token;
		return ;
	}
	append_token(&(*tokens)->next, token);
}
