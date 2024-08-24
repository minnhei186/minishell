/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:11:17 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 04:57:26 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/readline.h"
#include "../include/hashmap.h"
#include <stdio.h>

typedef struct s_map		t_map;

void	print_allenv(t_map *envmap)
{
	t_item	*cur;

	cur = envmap->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}

int	builtin_export(char **argv, t_map *envmap)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv(envmap);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(envmap, argv[i], true) < 0)
		{
			builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}
