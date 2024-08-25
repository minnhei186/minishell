/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:14:24 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 22:18:02 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_map *envmap)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
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
	return (status);
}
