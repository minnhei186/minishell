/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:35:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/03 19:30:28 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

/*
	Quotes
*/
void	remove_single_quote(char **dest, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dest, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

void	remove_double_quote(char **dest, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			append_char(dest, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected double quote");
}

// append_char -> skip_quote
void	append_single_quote(char **dest, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		append_char(dest, *p++);
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dest, *p++);
		}
		append_char(dest, *p++);
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

// append_char -> skip_quote
void	append_double_quote(char **dest, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		append_char(dest, *p++);
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			else if (is_variable(p))
				expand_variable_str(dest, &p, p);
			else if (is_special_parameter(p))
				expand_special_parameter_str(dest, &p, p, get_last_status);
			else
				append_char(dest, *p++);
		}
		append_char(dest, *p++);
		*rest = p;
	}
	else
		assert_error("Expected double quote");
}

/*
	Strings
*/
