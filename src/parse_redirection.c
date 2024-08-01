/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:12 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/31 22:00:41 by geonwkim         ###   ########.fr       */
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

t_node	*redirect_out(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->file_name = token_dup(token->next);
	node->target_fd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->file_name = token_dup(token->next);
	node->target_fd = STDIN_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*redirect_append(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND);
	node->file_name = token_dup(token->next);
	node->target_fd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*redirect_heredoc(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC);
	node->delimiter = token_dup(token->next);
	node->target_fd = STDIN_FILENO;
	*rest = token->next->next;
	return (node);
}
