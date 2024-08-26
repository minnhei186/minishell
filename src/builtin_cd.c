/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:30:51 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/26 21:52:13 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/builtin.h"

// bool	consume_path(char **rest, char *path, char *element)
// {
// 	size_t	element_len;

// 	element_len = ft_strlen(element);
// 	if (ft_strcmp(path, element, element_len) == 0)
// 	{
// 		if (path[element_len] == '\0' || path[element_len] == '/')
// 		{
// 			*rest = path + element_len;
// 			return (true);	
// 		}
// 	}
// 	return (false);
// }

// void	delete_last_element(char *path)
// {
// 	char	*start;
// 	char	*last_slash_ptr;

// 	start = path;
// 	last_slash_ptr = NULL;
// 	while (*path)
// 	{
// 		if (*path == '/')
// 			last_slash_ptr = path;
// 		path++;
// 	}
// 	if (last_slash_ptr != start)
// 		*last_slash_ptr = '\0';
// }

// void	append_lath_element(char *dest, char **rest, char *src)
// {
// 	size_t	element_len;

// 	element_len = 0;
// 	while (src[element_len] && src[element_len] != '/')
// 		element_len++;
// 	if (dest[ft_strlen(dest) - 1] != '/')
// 		ft_strcat(dest, "/");
// }
