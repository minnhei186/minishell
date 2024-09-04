/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:04:04 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/31 18:19:02 by geonwkim         ###   ########.fr       */
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

	if (name == NULL)
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

int	map_unset(t_map *map, const char *name)
{
	t_item	*cur;
	// t_item	prev;

	if (name == NULL || !is_identifier(name))
		return (-1);
	// prev = map->item_head;
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			free(cur->name);
			free(cur->value);
			free(map->environ);
			printf("map printall?? \n");
			return (0);
		}
		// prev = &prev->next;
		cur = cur->next;
	}
	cur->name = NULL;
	return (0);
}

// name, value 
// int	map_set(t_map *map, const char *name, const char *value)
// {
// 	t_item	*cur;

// 	if (name == NULL || !is_identifier(name))
// 		return (-1);
// 	cur = map->item_head.next;
// 	while (cur)
// 	{
// 		if (ft_strcmp(cur->name, name) == 0)
// 			break ;
// 		cur = cur->next;
// 	}
// 	if (cur)
// 	{
// 		free(cur->value);
// 		if (value == NULL)
// 			cur->value = NULL;
// 		else
// 		{
// 			cur->value = ft_strdup(value);
// 			if (cur->value == NULL)
// 				fatal_error("map_set strdup");
// 		}
// 	}
// 	else
// 	{
// 		if (value == NULL)
// 		{
// 			cur = item_new(ft_strdup(name), NULL);
// 			if (cur->name == NULL)
// 				fatal_error("strdup");
// 		}
// 		else
// 		{
// 			cur = item_new(ft_strdup(name), ft_strdup(value));
// 			if (cur->name == NULL || cur->value == NULL)
// 				fatal_error("strdup");
// 		}
// 		cur->next = map->item_head.next;
// 		map->item_head.next = cur;
// 	}
// 	return (0);
// }

// int	map_set(t_map *map, const char *name, const char *value)
// {
// 	t_item	*cur;

// 	if (!name || !is_identifier(name))
// 		return (-1);
// 	cur = map->item_head.next;
// 	while (cur && ft_strcmp(cur->name, name) != 0)
// 		cur = cur->next;
// 	if (cur)
// 	{
// 		free(cur->value);
// 		cur->value = value ? ft_strdup(value) : NULL;
// 		if (value && !cur->value)
// 			fatal_error("map_set strdup");
// 	}
// 	else
// 	{
// 		cur = item_new(ft_strdup(name), value ? ft_strdup(value) : NULL);
// 		if (!cur->name || (value && !cur->value))
// 			fatal_error("strdup");
// 		cur->next = map->item_head.next;
// 		map->item_head.next = cur;
// 	}
// 	return (0);
// }

// int	map_put(t_map *map, const char *string, bool allow_empty_value)
// {
// 	int		result;
// 	char	*name_end;
// 	char	*name;
// 	char	*value;

// 	name_end = ft_strchr(string, '=');
// 	if (name_end == NULL)
// 	{
// 		if (!allow_empty_value)
// 			return (-1);
// 		name = ft_strdup(string);
// 		value = NULL;
// 		if (name == NULL)
// 			fatal_error("strdup");
// 	}
// 	else
// 	{
// 		name = ft_strndup(string, name_end - string);
// 		value = ft_strdup(name_end + 1);
// 		if (name == NULL || value == NULL)
// 			fatal_error("strdup");
// 	}
// 	result = map_set(map, name, value);
// 	free(name);
// 	free(value);
// 	return (result);
// }
