/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:11:17 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/08 21:55:25 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/hashmap.h"
#include <stdio.h>

char	*map_get(t_map *map, const char *name);

// Function to count the number of environment variables
size_t	count_env(t_map *envmap)
{
	t_item	*cur;
	size_t	count;

	count = 0;
	cur = envmap->item_head.next;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

// Function to copy the environment variable names into an array
char	**get_env_names(t_map *envmap)
{
	size_t	count;
	char	**env_names;
	t_item	*cur;
	size_t	i;

	count = count_env(envmap);
	env_names = malloc(sizeof(char *) * (count + 1));
	if (!env_names)
		return (NULL);
	cur = envmap->item_head.next;
	i = 0;
	while (cur)
	{
		env_names[i] = ft_strdup(cur->name);
		cur = cur->next;
		i++;
	}
	env_names[i] = NULL;
	return (env_names);
}

// Custom bubble sort function with while loops
void	bubble_sort_env_names(char **env_names, size_t count)
{
	size_t	i;
	size_t	j;
	char	*temp;
	int		swapped;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		swapped = 0;
		while (j < count - i - 1)
		{
			if (strcmp(env_names[j], env_names[j + 1]) > 0)
			{
				temp = env_names[j];
				env_names[j] = env_names[j + 1];
				env_names[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

void	print_allenv(t_map *envmap)
{
	char	**env_names;
	size_t	count;
	size_t	i;

	env_names = get_env_names(envmap);
	if (!env_names)
		return ;
	count = count_env(envmap);
	bubble_sort_env_names(env_names, count);
	i = 0;
	while (i < count)
	{
		print_env_for_name(envmap, env_names[i]);
		free(env_names[i]);
		i++;
	}
	free(env_names);
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
