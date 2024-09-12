/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:11:17 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 22:12:02 by geonwkim         ###   ########.fr       */
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
			if (ft_strcmp(env_names[j], env_names[j + 1]) > 0)
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

// int	builtin_export(char **argv, t_map *envmap)
// {
// 	size_t	i;
// 	int		status;

// 	if (argv[1] == NULL)
// 	{
// 		print_allenv(envmap);
// 		return (0);
// 	}
// 	status = 0;
// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (map_put(envmap, argv[i], true) < 0)
// 		{
// 			builtin_error("export", argv[i], "not a valid identifier");
// 			status = 1;
// 		}
// 		i++;
// 	}
// 	return (status);
// }

int	handle_append(t_map *envmap, const char *arg)
{
	char	*var_name;
	char	*new_value;
	char	*current_value;
	char	*concatenated_value;
	char	*plus_equal_sign;
	char	*test;
	char	*test1;
	char	*test2;

	// Locate the "+=" in the argument to separate name and value
	plus_equal_sign = ft_strstr(arg, "+=");
	if (!plus_equal_sign)  // Ensure "+=" is present in the string
		return (1);

	// Extract the variable name (everything before "+=")
	var_name = ft_substr(arg, 0, plus_equal_sign - arg);  
	if (!var_name)  // Memory allocation failed
		return (1);

	// Extract the value (everything after "+=")
	new_value = ft_strdup(plus_equal_sign + 2);  
	if (!new_value) 
	{
		free(var_name);  // Free var_name since new_value allocation failed
		return (1);
	}

	// Retrieve the current value of the variable, if it exists
	current_value = map_get(envmap, var_name);
	printf("var_name = %s\n", var_name);
	printf("new_var = %s\n", new_value);
	printf("current_var = %s\n", current_value);

	if (current_value)
	{
		// Append the new value to the current value
		concatenated_value = ft_strjoin(current_value, new_value);
	}
	else
	{
		// If the variable doesn't exist, just assign the new value
		concatenated_value = ft_strdup(new_value);
	}

	// Free temporary values (new_value and var_name)
	free(new_value);
	// free(var_name);

	test = ft_strdup(var_name);
	test1 = ft_strjoin(test, "=");
	test2 = ft_strjoin(test1, concatenated_value);
	// Ensure successful memory allocation before storing the value
	if (!concatenated_value || map_put(envmap, test2, true) < 0)
	{
		free(concatenated_value);  // Free concatenated_value in case of failure
		return (1);
	}

	// Successfully stored the concatenated value
	free(concatenated_value);
	return (0);
}

int	builtin_export(char **argv, t_map *envmap)
{
	size_t	i;
	int		status;

	if (!argv[1])
	{
		print_allenv(envmap);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_strstr(argv[i], "+="))  // Handle appending using `+=`
			status |= handle_append(envmap, argv[i]);
		else if (map_put(envmap, argv[i], true) < 0)  // Regular export case
		{
			builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}
