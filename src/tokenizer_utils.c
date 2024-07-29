/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:37:55 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 01:32:50 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

// startswith
bool	operators_cmp(char *str, char *key_op)
{
	return (ft_memcmp(str, key_op, ft_strlen(key_op)) == 0);
}

bool	is_operator(char *input_p)
{
	static char *const	operators[] = {"||", "&", "&&", \
						";", ";;", "(", ")", "|", "\n"};
	size_t				i;

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
