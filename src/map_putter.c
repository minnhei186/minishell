/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_putter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:14:55 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/29 00:15:43 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hashmap.h"

static void	get_name_value(const char *string, bool allow_empty_value, \
	char **name, char **value)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		if (!allow_empty_value)
			fatal_error("missing '=' and empty value not allowed");
		*name = ft_strdup(string);
		*value = NULL;
	}
	else
	{
		*name = ft_strndup(string, name_end - string);
		*value = ft_strdup(name_end + 1);
	}
	if (*name == NULL || (name_end != NULL && *value == NULL))
		fatal_error("strdup");
}

int	map_put(t_map *map, const char *string, bool allow_empty_value)
{
	char	*name;
	char	*value;
	int		result;

	get_name_value(string, allow_empty_value, &name, &value);
	result = map_set(map, name, value);
	free(name);
	free(value);
	return (result);
}
