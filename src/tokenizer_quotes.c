/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:04:01 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 18:08:31 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"

void	skip_single_quote(char **line, t_status *status)
{
	(*line)++;
	while (**line && **line != SINGLE_QUOTE_CHAR)
		(*line)++;
	if (**line == '\0')
		tokenize_error("Unclosed single quote", line, *line, \
		status);
	else
		(*line)++;
}

void	skip_double_quote(char **line, t_status *status)
{
	(*line)++;
	while (**line && **line != DOUBLE_QUOTE_CHAR)
		(*line)++;
	if (**line == '\0')
		tokenize_error("Unclosed double quote", line, *line, \
		status);
	else
		(*line)++;
}

// There is no space to write down more function in tokenizer_utils
// So I moved some function that should be inside of tokenizer_utils
// to the tokenizer_quotes.c file
bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}
