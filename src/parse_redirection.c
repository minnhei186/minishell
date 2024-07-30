/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:12 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 20:11:10 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"
#include	"../include/error.h"
#include	"../libft/libft.h"

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->file_name = token_dup(tok->next);
	node->target_fd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

void	append_command_element(t_node *command, t_token **rest, t_token *token)
{
	if (token->kind == TK_WORD)
	{
		append_token(&command->args, token_dup(token));
		token = token->next;
	}
	else if (equal_op(token, ">") && token->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&token, token));
	else
		todo("append_command_element");
	*rest = token;
}

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}
