/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:14:24 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/31 14:47:14 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

int	builtin_unset(char **argv, t_map *envmap)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	printf("Now unset \n");
	while (argv[i])
	{
		if (map_unset(envmap, argv[i]) < 0)
		{
			builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	printf("Now (printall) -> ");
	map_printall(envmap);
	return (status);
}
