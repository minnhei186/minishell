/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:39:25 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/13 01:01:24 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include <errno.h>

bool	is_numeric(char *s)
{
	if (!ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

// int	builtin_exit(char **argv, t_status *status)
// {
// 	long	res;
// 	char	*arg;
// 	char	*endptr;

// 	ft_putendl_fd("exit", 1);
// 	if (argv[1] == NULL)
// 		exit(status->last_status);
// 	if (argv[2])
// 	{
// 		xperror("exit: too many arguments");
// 		return (1);
// 	}
// 	arg = argv[1];
// 	if (is_numeric(arg))
// 	{
// 		errno = 0;
// 		res = strtol(arg, &endptr, 10);
// 		if (errno == 0 && *endptr == '\0')
// 			exit((int)res);
// 	}
// 	xperror("exit: numeric argument required");
// 	exit(255);
// }

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static long	convert_to_long(char *arg)
{
	long	res;
	char	*endptr;

	errno = 0;
	res = strtol(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
	{
		print_numeric_error(arg);
		exit(2);
	}
	return (res);
}

// exit aa | exitした時に必ず１３０が出ないと行けないが、
// 何故かBashとMinishellどっちても０が現れる。。
int	builtin_exit(char **argv, t_status *status)
{
	long	res;

	ft_putendl_fd("exit", 1);
	if (argv[1] == NULL)
		exit(status->last_status);
	if (!is_numeric(argv[1]))
	{
		print_numeric_error(argv[1]);
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			exit(130);
		else
			exit(2);
	}
	res = convert_to_long(argv[1]);
	if (argv[2])
	{
		xperror("exit: too many arguments");
		return (1);
	}
	exit((int)res);
}
