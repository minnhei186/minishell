/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:10:32 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 01:01:01 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"error.h"

void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	todo(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

/* 
	To avoid using Global variable, 
	I generated the function that stores syntax_error state as false
*/
// bool	*get_syntax_error_ptr(void)
// {
// 	bool	syntax_error;
// 	syntax_error = false;
// 	return (&syntax_error);
// }

/*
	Reset the syntax_error state as the false
*/
// void	reset_syntax_error(void)
// {
// 	bool	*syntax_error;
// 	syntax_error = get_syntax_error_ptr();
// 	*syntax_error = false;
// }
