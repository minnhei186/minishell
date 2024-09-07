/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:14:24 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/07 21:46:24 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	map_contains_key(t_map *envmap, const char *key)
{
	t_item	*current;

	if (!envmap || !key)
		return (0);
	current = envmap->item_head.next;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	builtin_unset(char **argv, t_map *envmap)
{
	int		status;
	size_t	i;

	if (!envmap || !argv)
		return (1);
	status = 0;
	i = 1;
	printf("Now unset \n");
	while (argv[i])
	{
		if (argv[i][0] == '\0' || !is_valid_identifier(argv[i]))
		{
			builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		else
		{
			if (!map_contains_key(envmap, argv[i]))
			{
				builtin_error("unset", argv[i], "not found in environment");
				status = 1;
			}
			else if (map_unset(envmap, argv[i]) < 0)
			{
				builtin_error("unset", argv[i], "failed to remove");
				status = 1;
			}
		}
		i++;
	}
	printf("Now (printall) -> ");
	map_printall(envmap);
	return (status);
}
