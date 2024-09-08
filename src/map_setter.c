/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:13:08 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/09 00:26:46 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hashmap.h"

static void	set_value(t_item *cur, const char *value)
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

static t_item	*create_item(const char *name, const char *value)
{
	t_item	*new_item;

	if (value == NULL)
		new_item = item_new(ft_strdup(name), NULL);
	else
		new_item = item_new(ft_strdup(name), ft_strdup(value));
	if (!new_item->name || (value && !new_item->value))
		fatal_error("strdup");
	return (new_item);
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*cur;

	if (name == NULL || !is_identifier(name))
		return (-1);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			set_value(cur, value);
			return (0);
		}
		cur = cur->next;
	}
	cur = create_item(name, value);
	cur->next = map->item_head.next;
	map->item_head.next = cur;
	return (0);
}
