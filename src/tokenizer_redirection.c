/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:43:43 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/12 22:33:31 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"
#include	"../include/error.h"
#include	"../libft/libft.h"

// bool	is_redirection_operator(const char *s)
// {
// 	static char *const	operators[] = {">", "<", ">>", "<<"};
// 	size_t				i;
// 	i = 0;
// 	while (i < sizeof(operators) / sizeof(*operators))
// 	{
// 		if (startswith(s, operators[i]))
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }
