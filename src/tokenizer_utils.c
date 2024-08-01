/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:37:55 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 17:01:54 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && ft_strchr("|&;()<>\n", c));
}

// startswith
bool	operators_cmp(char *str, char *key_op)
{
	return (ft_memcmp(str, key_op, ft_strlen(key_op)) == 0);
}

bool	is_word(char *s)
{
	return (*s && !is_metacharacter(*s));
}
