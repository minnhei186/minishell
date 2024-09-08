/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 00:43:59 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/08 22:21:09 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

// int	builtin_echo(char **argv)
// {
// 	bool	is_first_arg;
// 	bool	echo_newline;
// 	size_t	i;

// 	i = 1;
// 	echo_newline = true;
// 	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
// 	{
// 		i++;
// 		echo_newline = false;
// 	}
// 	is_first_arg = true;
// 	while (argv[i])
// 	{
// 		if (!is_first_arg)
// 			write(STDOUT_FILENO, " ", 1);
// 		is_first_arg = false;
// 		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
// 		i++;
// 	}
// 	if (echo_newline)
// 		write(STDOUT_FILENO, "\n", 1);
// 	return (0);
// }

static bool	is_n_flag(char *arg)
{
	size_t	j;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (false);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static void	print_args(char **argv, size_t i)
{
	bool	is_first_arg;

	is_first_arg = true;
	while (argv[i])
	{
		if (!is_first_arg)
			write(STDOUT_FILENO, " ", 1);
		is_first_arg = false;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
}

int	builtin_echo(char **argv)
{
	bool	echo_newline;
	size_t	i;

	i = 1;
	echo_newline = true;
	while (argv[i] && is_n_flag(argv[i]))
	{
		echo_newline = false;
		i++;
	}
	print_args(argv, i);
	if (echo_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
