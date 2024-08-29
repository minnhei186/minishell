/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 00:43:59 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/30 00:44:40 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

int	builtin_echo(char **argv)
{
	bool	is_first_arg;
	bool	echo_newline;
	size_t	i;

	i = 1;
	echo_newline = true;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i++;
		echo_newline = false;
	}
	is_first_arg = true;
	while (argv[i])
	{
		if (!is_first_arg)
			write(STDOUT_FILENO, " ", 1);
		is_first_arg = false;
		write(STDOUT_FILENO, argv[i], strlen(argv[i]));
		i++;
	}
	if (echo_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
