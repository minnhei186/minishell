/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:50:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/30 03:06:06 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "../include/minishell.h"
#include <linux/limits.h>

static void	envmap_init(t_map *map, char **ep);

char	*xgetenv(t_map *map, const char *name)
{
	return (map_get(map, name));
}

// char	*xgetenv(t_map *map, const char *name)
// {
// 	t_item	*item;

// 	item = map_get(map, name);
// 	if (item == NULL)
// 		return (NULL);
// 	return (item->value);
// }

void	initenv(t_map **map)
{
	extern char	**environ;

	*map = map_new();
	envmap_init(*map, environ);
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_item	*item;

	size = map_len(map, false) + 1;
	map->environ = ft_calloc(size, sizeof(char *));
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value)
		{
			map->environ[i] = item_get_string(item);
			i++;
		}
		item = item->next;
	}
	map->environ[i] = NULL;
	return (map->environ);
}

static void	envmap_init(t_map *map, char **ep)
{
	char	cwd[PATH_MAX];

	while (*ep)
	{
		map_put(map, *ep, false);
		ep++;
	}
	if (map_get(map, "SHIVL") == NULL)
		map_set(map, "SHLVL", "1");
	if (map_get(map, "PWD") == NULL)
	{
		getcwd(cwd, PATH_MAX);
		map_set(map, "PWD", cwd);
	}
	if (map_get(map, "OLDPWD") == NULL)
		map_set(map, "OLDPWD", NULL);
}
