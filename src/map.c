/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:04:04 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/24 21:06:50 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/hashmap.h"

#include <stdio.h>
#include <string.h>

bool	is_identifier(const char *s);
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

t_item	*item_new(char *name, char *value)
{
	t_item	*item;

	item = ft_calloc(1, sizeof(*item));
	if (item == NULL)
		fatal_error("calloc");
	item->name = name;
	item->value = value;
	return (item);
}

char	*item_get_string(t_item *item)
{
	size_t	strsize;
	char	*string;

	strsize = ft_strlen(item->name) + 2;
	if (item->value)
		strsize += ft_strlen(item->value);
	string = malloc(strsize);
	if (string == NULL)
		fatal_error("malloc");
	ft_strlcpy(string, item->name, strsize);
	if (item->value)
	{
		ft_strlcat(string, "=", strsize);
		ft_strlcat(string, item->value, strsize);
	}
	return (string);
}

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
	t_item	*prev;

	if (name == NULL || !is_identifier(name))
		return (-1);
	prev = &map->item_head;
	cur = map->item_head.next;
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
	return (0);
}

// name, value 
int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*cur;

	if (name == NULL || !is_identifier(name))
		return (-1);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			break ;
		cur = cur->next;
	}
	// found
	if (cur)
	{
		free(cur->value);
		if (value == NULL)
			cur->value = NULL;
		else
		{
			cur->value = ft_strdup(value);
			if (cur->value == NULL)
				fatal_error("map_set strdup");
		}
	}
	// not found
	else
	{
		if (value == NULL)
		{
			cur = item_new(ft_strdup(name), NULL);
			if (cur->name == NULL)
				fatal_error("strdup");
		}
		else
		{
			cur = item_new(ft_strdup(name), ft_strdup(value));
			if (cur->name == NULL || cur->value == NULL)
				fatal_error("strdup");
		}
		cur->next = map->item_head.next;
		map->item_head.next = cur;
	}
	return (0);
}

int	map_put(t_map *map, const char *string, bool allow_empty_value)
{
	int		result;
	char	*name_end;
	char	*name;
	char	*value;

	name_end = ft_strchr(string, '=');
	// value is null
	if (name_end == NULL)
	{
		if (!allow_empty_value)
			return (-1);
		name = ft_strdup(string);
		value = NULL;
		if (name == NULL)
			fatal_error("strdup");
	}
	// value is non null
	else
	{
		name = ft_strndup(string, name_end - string);
		value = ft_strdup(name_end + 1);
		if (name == NULL || value == NULL)
			fatal_error("strdup");
	}
	result = map_set(map, name, value);
	free(name);
	free(value);
	return (result);
}

size_t	map_len(t_map *map, bool count_null_value)
{
	size_t	len;
	t_item	*item;

	len = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value || count_null_value)
			len++;
		item = item->next;
	}
	return (len);
}
