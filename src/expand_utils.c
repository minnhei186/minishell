/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:40:26 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/03 16:28:40 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

/*
	PARAMETERS
	A parameter is an entity that stores values.  It can be a name, a
	number, or one of the special characters listed below under Special
	Parameters.  A variable is a parameter denoted by a name.  A variable
	has a value and zero or more attributes.  Attributes are assigned using
	the declare builtin command (see declare below in SHELL BUILTIN
	COMMANDS).

	A parameter is set if it has been assigned a value.  The null string is
	a valid value.  Once a variable is set, it may be unset only by using
	the unset builtin command (see SHELL BUILTIN COMMANDS below).

	DEFINITIONS
	The following definitions are used throughout the rest of this document.
	blank  A space or tab.
	word   A sequence of characters considered as a single unit by the shell.
						Also known as a token.
	name   A word consisting only of alphanumeric characters and underscores, 
						and beginning with an alphabetic character or an underscore.
						Also referred to as an identifier.
	metacharacter
			A character that, when unquoted, separates words.  One of the following:
			|  & ; ( ) < > space tab
	control operator
			A token that performs a control function.  It is one of the following symbols:
			|| & && ; ;; ( ) | <newline>
*/

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

void	expand_variable_str(char **dest, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	if (*p != '$')
		assert_error("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		assert_error(\
			"Variable must starts with alphabetic character of underscore.");
	append_char(&name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dest, *value++);
	*rest = p;
}

void	expand_variable_token(t_token *token)
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
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(token->word);
	token->word = new_word;
	expand_variable_token(token->next);
}
