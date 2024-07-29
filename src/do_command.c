/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:00:18 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/30 01:32:13 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*abs_path_get(void)
{
	char		*path;
	const char	*temp;

	path = NULL;
	temp = getenv("PATH");
	if (temp)
	{
		path = (char *)malloc(ft_strlen(temp) + 1);
		if (!path)
		{
			perror("malloc error");
			exit(1);
		}
		strcpy(path, temp);
	}
	else
	{
		perror("environmental variables not found");
		exit(1);
	}
	return (path);
}

char	*check_path(char *abs_path, const char *line)
{
	char	f_path[PATH_MAX];

	ft_bzero(f_path, PATH_MAX);
	ft_strlcat(strncpy(f_path, abs_path, PATH_MAX - 1), "/", PATH_MAX);
	ft_strlcat(f_path, line, PATH_MAX);
	if (access(f_path, 0) == 0)
		return (ft_strdup(f_path));
	return (NULL);
}

char	*find_path(const char *line)
{
	char	*abs_path;
	char	*path_tail;
	char	*tmp_free;
	char	*found_path;

	abs_path = abs_path_get();
	tmp_free = abs_path;
	path_tail = ft_strchr(abs_path, ':');
	while (path_tail)
	{
		*path_tail = '\0';
		found_path = check_path(abs_path, line);
		if (found_path)
		{
			free(tmp_free);
			return (found_path);
		}
		abs_path = path_tail + 1;
		path_tail = ft_strchr(abs_path, ':');
	}
	found_path = check_path(abs_path, line);
	free(tmp_free);
	return (found_path);
}

// char	*find_path(char *line)
// {
// 	char	*abs_path;
// 	char	f_path[PATH_MAX];
// 	char	*path_tail;
// 	char	*tmp_free;

// 	abs_path = abs_path_get();
// 	tmp_free = abs_path;
// 	path_tail = strchr(abs_path, ':');
// 	while (path_tail)
// 	{
// 		bzero(f_path, PATH_MAX);
// 		strncpy(f_path, abs_path, path_tail - abs_path);
// 		strlcat(f_path, "/", sizeof(f_path));
// 		strlcat(f_path, line, sizeof(f_path));
// 		if (access(f_path, 0) == 0)
// 		{
// 			free(tmp_free);
// 			abs_path = strdup(f_path);
// 			return (abs_path);
// 		}
// 		abs_path = path_tail;
// 		abs_path++;
// 		path_tail = strchr(abs_path, ':');
// 	}
// 	bzero(f_path, PATH_MAX);
// 	strncpy(f_path, abs_path, sizeof(f_path) - 1);
// 	strlcat(f_path, "/", sizeof(f_path));
// 	strlcat(f_path, line, sizeof(f_path));
// 	if (access(f_path, 0) == 0)
// 	{
// 		free(tmp_free);
// 		abs_path = strdup(f_path);
// 		return (abs_path);
// 	}
// 	else
// 	{
// 		free(tmp_free);
// 		return (NULL);
// 	}
// }

char	**subsequent_argv_recursive(t_token *tok, int nargs, char **argv)
{
	if (tok == NULL || tok->kind == TK_EOF)
		return (argv);
	argv = realloc(argv, (nargs + 2) * sizeof(char *));
	argv[nargs] = ft_strdup(tok->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (subsequent_argv_recursive(tok->next, nargs + 1, argv));
}

char	**token_to_argv(t_token *tok)
{
	char	**argv;

	argv = (char **)calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (subsequent_argv_recursive(tok, 0, argv));
}
