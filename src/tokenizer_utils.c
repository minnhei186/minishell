/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:37:55 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/15 15:55:45 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	return (c && strchr("|&;*() <>\t\n", c));
}

bool	operators_cmp(char *str, char *key_op)
{
	return (memcmp(str, key_op, strlen(key_op)) == 0);
}

bool	is_operator(char *input_p)
{
	static char *const	operators;
	size_t				i;

	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|",
		"\n"};
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (operators_cmp(input_p, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_word(char *s)
{
	return (*s && !is_metacharacter(*s));
}
