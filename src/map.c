/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:04:04 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/09 01:18:25 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/hashmap.h"

#include <stdio.h>
#include <string.h>

bool	is_identifier(const char *s);
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);

t_map	*map_new(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(*map));
	if (map == NULL)
		fatal_error("calloc");
	return (map);
}

char	*map_get(t_map *map, const char *name)
{
	t_item	*cur;

	if (name == NULL || map == NULL)
		return (NULL);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

// free(map->environ)するとValgrindからエラーが発生します
// int	map_unset(t_map *map, const char *name)
// {
// 	t_item	*cur;

// 	if (name == NULL || !is_identifier(name))
// 		return (-1);
// 	cur = map->item_head.next;
// 	while (cur)
// 	{
// 		if (ft_strcmp(cur->name, name) == 0)
// 		{
// 			free(cur->name);
// 			free(cur->value);
// 			free(map->environ);
// 			return (0);
// 		}
// 		cur = cur->next;
// 	}
// 	cur->name = NULL;
// 	return (0);
// }


// free(map->environ)するとValgrindからエラーが発生します
int	map_unset(t_map *map, const char *name)
{
	t_item	*cur;
	t_item	*prev;

	if (name == NULL || !is_identifier(name))
		return (-1);
	prev = &map->item_head;
	printf("prev %p - %s\n", prev->next, prev->next->value);
	cur = map->item_head.next;
	printf("cur %p - %s\n", cur->next, cur->next->value);
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			prev->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = prev->next;
		cur = cur->next;
	}
	cur->name = NULL;
	return (0);
}
