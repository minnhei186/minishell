/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:15:49 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/30 03:19:27 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"

/*
	print_desc "SIGTERM to SHELL"
	(sleep 0.01; pkill -SIGTERM bash;
	sleep 0.01; pkill -SIGTERM minishell) &
	assert './infinite_loop' 2>/dev/null

	-> ここSignalで使っている()と;はBonus課題、またMandatoryとBonusどっちでも入ってないため
	やらなくても大丈夫

	-> ただ、sleep 0.01、またはpkill -SIGTERM bashコマンドが動かないと行けない
*/
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
	// else
	// {
	// 	fprintf(stderr,
	// 	"minishell: syntax error near unexpected token `%s'\n", token->word);
	// 	// *rest = token->next;
	// 	*rest = NULL;
	// 	//debug
	// 	printf("rest address =[ %p ]\n", rest);
	// 	//end
	// 	return ;
	// }
	else
		parse_error(&token, token);
	*rest = token;
}

void	append_node(t_node **node, t_node *element)
{
	if (*node == NULL)
	{
		*node = element;
		return ;
	}
	append_node(&(*node)->next, element);
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
