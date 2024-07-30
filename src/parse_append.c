/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:15:49 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 23:43:15 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"
#include	"../include/error.h"
#include	"../libft/libft.h"

void	append_command_element(t_node *command, t_token **rest, t_token *token)
{
	if (token->kind == TK_WORD)
	{
		append_token(&command->args, token_dup(token));
		token = token->next;
	}
	else if (equal_op(token, ">") && token->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&token, token));
	else if (equal_op(token, "<") && token->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_in(&token, token));
	else if (equal_op(token, ">>") && token->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_append(&token, token));
	else if (equal_op(token, "<<") && token->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_heredoc(&token, token));
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
