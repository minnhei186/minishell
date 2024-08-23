/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:28:48 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/23 19:33:19 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "readline.h"
# include "builtin.h"
# include "last_status.h"
# include "error.h"
# include "../libft/libft.h"

/*
	Struct for Environment & Hashmap
*/
typedef struct s_map		t_map;
typedef struct s_item		t_item;

struct						s_item
{
	char					*name;
	char					*value;
	t_item					*next;	
};

struct						s_map
{
	t_item					item_head;
};

extern t_map					*envmap;

/* Hashmap.c */
t_item	*item_new(char *name, char *value);
char	*item_get_string(t_item *item);

t_map	*map_new(void);
char	*map_get(t_map *map, const char *name);
int		map_put(t_map *map, const char *string, bool allow_empty_value);
int		map_set(t_map *map, const char *name, const char *value);
int		map_unset(t_map *map, const char *name);

size_t	map_len(t_map *map, bool count_null_value);
void	map_printall(t_map *map);

/* env.c */
char	*xgetenv(t_map *envmap, const char *name);
void	initenv(t_map **envmap);
char	**get_environ(t_map *map);

#endif
