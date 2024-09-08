/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:10:32 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/08 21:56:29 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/error.h"

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

void	xperror(const char *l)
{
	perror_prefix();
	perror(l);
}

void	builtin_error(const char *func, const char *name, const char *err)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: ", func);
	if (name)
		dprintf(STDERR_FILENO, "`%s': ", name);
	dprintf(STDERR_FILENO, "%s\n", err);
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
