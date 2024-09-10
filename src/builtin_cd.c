/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:30:51 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/10 22:14:37 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/builtin.h"

bool	consume_path(char **rest, char *path, char *element)
{
	size_t	element_len;

	element_len = ft_strlen(element);
	if (ft_strncmp(path, element, element_len) == 0)
	{
		if (path[element_len] == '\0' || path[element_len] == '/')
		{
			*rest = path + element_len;
			return (true);
		}
	}
	return (false);
}

void	delete_last_element(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

void	append_path_element(char *dst, char **rest, char *src)
{
	size_t	elm_len;

	elm_len = 0;
	while (src[elm_len] && src[elm_len] != '/')
		elm_len++;
	if (dst[ft_strlen(dst) - 1] != '/')
		ft_strcat(dst, "/");
	ft_strncat(dst, src, elm_len);
	*rest = src + elm_len;
}

char	*resolve_pwd(char *oldpwd, char *path)
{
	char	newpwd[PATH_MAX];
	char	*dup;

	if (oldpwd == NULL)
		return (NULL);
	if (*path == '/')
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_element(newpwd);
		else
			append_path_element(newpwd, &path, path);
	}
	dup = ft_strdup(newpwd);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}

// if (home == NULL), builtin_error("cd", NULL, "HOME not set");
int	builtin_cd(char **argv, t_map *envmap)
{
	char	path[PATH_MAX];
	char	*newpwd;
	char	*oldpwd;

	oldpwd = map_get(envmap, "PWD");
	map_set(envmap, "OLDPWD", oldpwd);
	if (!argv[1])
	{
		if (!(map_get(envmap, "HOME")))
			return (builtin_error("cd", NULL, "HOME not set"), 1);
		ft_strlcpy(path, map_get(envmap, "HOME"), PATH_MAX);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX);
	if (chdir(path) < 0)
		return (builtin_error("cd", NULL, "No such file or directory"), 1);
	newpwd = resolve_pwd(oldpwd, path);
	map_set(envmap, "PWD", newpwd);
	free(newpwd);
	return (0);
}

// int	builtin_cd(char **argv, t_map *envmap)
// {
// 	char	*home;
// 	char	*oldpwd;
// 	char	path[PATH_MAX];
// 	char	*newpwd;

// 	oldpwd = map_get(envmap, "PWD");
// 	map_set(envmap, "OLDPWD", oldpwd);
// 	if (argv[1] == NULL)
// 	{
// 		home = map_get(envmap, "HOME");
// 		if (home == NULL)
// 		{
// 			builtin_error("cd", NULL, "HOME not set");
// 			return (1);
// 		}
// 		ft_strlcpy(path, home, PATH_MAX);
// 	}
// 	else
// 		ft_strlcpy(path, argv[1], PATH_MAX);
// 	if (chdir(path) < 0)
// 	{
// 		builtin_error("cd", NULL, "chdir");
// 		return (1);
// 	}
// 	newpwd = resolve_pwd(oldpwd, path);
// 	map_set(envmap, "PWD", newpwd);
// 	free(newpwd);
// 	return (0);
// }
