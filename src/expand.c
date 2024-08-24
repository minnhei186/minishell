/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:28:03 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/24 20:50:28 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	remove_quote(t_token *token)
{
	char	*new_word;
	char	*p;

	if (token == NULL || token->kind != TK_WORD || token->word == NULL)
		return ;
	p = token->word;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			remove_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			remove_double_quote(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(token->word);
	token->word = new_word;
	remove_quote(token->next);
}

void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args);
	remove_quote(node->file_name);
	remove_quote(node->delimiter);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->cmd);
	expand_quote_removal(node->next);
}

/*
	Here Documents
	- 1. The format of here-document is
		= <<[-]word
				here-document
		delimiter

	- 2. No parameter expansion, command subsitution, arithmetric expansion,
		or pathname expansion is performed on word
	
		= remove_quote(node->delimiter);

	- 3. 
		= `delimiter` として指定される `word`に対しては 
			`parameter expansion` が行われない
		= `word` の `quote removal`は行われる
		= `word` が引用符で囲まれていない場合は、here-document自体に 
			`parameter expansion` が行われる（逆にいえば`word` 
			が引用符で囲まれている場合には行われない）
	
	- 4. The delimiter should not be expanded for several important reasons:
	
*/
void	expand_variable(t_node *node, t_status *status)
{
	if (node == NULL)
		return ;
	expand_variable_token(node->args, status);
	expand_variable_token(node->file_name, status);
	expand_variable(node->redirects, status);
	expand_variable(node->cmd, status);
	expand_variable(node->next, status);
}

// Expand from expand_quote_removal
/*
  @Param: t_node *node
  
*/
void	expand(t_node *node, t_status *status)
{
	expand_variable(node, status);
	expand_quote_removal(node);
}
