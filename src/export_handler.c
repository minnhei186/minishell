/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:08:01 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 23:16:17 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/hashmap.h"
#include <stdio.h>

// Helper function to handle export with append ("+=")
int	handle_export_append(t_map *envmap, char *arg)
{
	if (handle_append(envmap, arg) != 0)
	{
		builtin_error("export", arg, "not a valid identifier");
		return (1);
	}
	return (0);
}

// Helper function to handle export without '='
int	handle_export_no_equals(char *arg, t_map *envmap)
{
	if (!map_get(envmap, arg))
	{
		printf("declare -x %s\n", arg);
	}
	else
	{
		print_allenv(envmap);
	}
	return (0);
}

int	handle_append(t_map *envmap, const char *arg)
{
	char	*var_name;
	char	*new_value;
	char	*current_value;
	char	*joined_value;
	char	*plus_equal_sign;

	plus_equal_sign = ft_strstr(arg, "+=");
	if (!plus_equal_sign)
		return (1);
	var_name = get_var_name(arg, plus_equal_sign);
	new_value = get_new_value(plus_equal_sign);
	if (validate_and_free(var_name, new_value))
		return (1);
	current_value = map_get(envmap, var_name);
	joined_value = concat_values(current_value, new_value);
	free(new_value);
	if (!joined_value || store_final_value(envmap, var_name, joined_value) < 0)
	{
		free(joined_value);
		free(var_name);
		return (1);
	}
	free(joined_value);
	free(var_name);
	return (0);
}
