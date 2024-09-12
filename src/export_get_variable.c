/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:09:39 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 23:16:54 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/hashmap.h"
#include <stdio.h>

char	*get_var_name(const char *arg, const char *plus_equal_sign)
{
	return (ft_substr(arg, 0, plus_equal_sign - arg));
}

char	*get_new_value(const char *plus_equal_sign)
{
	return (ft_strdup(plus_equal_sign + 2));
}

char	*concat_values(const char *current_value, const char *new_value)
{
	if (current_value)
		return (ft_strjoin(current_value, new_value));
	return (ft_strdup(new_value));
}

int	store_final_value(t_map *envmap, const char *var_name, \
	const char *joined_value)
{
	char	*var_with_equal;
	char	*final_string;
	int		result;

	var_with_equal = ft_strjoin(var_name, "=");
	final_string = ft_strjoin(var_with_equal, joined_value);
	result = map_put(envmap, final_string, true);
	free(var_with_equal);
	free(final_string);
	return (result);
}

int	validate_and_free(char *var_name, char *new_value)
{
	if (!var_name || !new_value)
	{
		free(var_name);
		free(new_value);
		return (1);
	}
	return (0);
}
