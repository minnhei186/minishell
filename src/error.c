/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:45:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/15 23:28:05 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/* 
	Assertion Error
	1. fprintf(stderr, "Error: %s\n", message);
	-> fwriteと動き方が全く同じ、しかし、理論的に連結されているディバイスと
	全ての文字列を
*/
void	assert_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/* Fatal Error */
void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}
