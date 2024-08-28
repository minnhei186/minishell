/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:00:18 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/28 21:44:37 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*abs_path_get(t_status *p_status)
{
	char		*path;
	const char	*temp;

	path = NULL;
	// temp = map_get(p_status->env_map, "PATH");
	temp = xgetenv(p_status->env_map, "PATH");
	printf("%s\n", temp);
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
		// perror("environmental variables not found");
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

char	*find_path(const char *line, t_status *p_status)
{
	char	*abs_path;
	char	*path_tail;
	char	*tmp_free;
	char	*found_path;

	abs_path = abs_path_get(p_status);
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
// 	path_tail = ft_strchr(abs_path, ':');
// 	while (path_tail)
// 	{
// 		ft_bzero(f_path, PATH_MAX);
// 		strncpy(f_path, abs_path, path_tail - abs_path);
// 		ft_strlcat(f_path, "/", sizeof(f_path));
// 		ft_strlcat(f_path, line, sizeof(f_path));
// 		if (access(f_path, 0) == 0)
// 		{
// 			free(tmp_free);
// 			abs_path = strdup(f_path);
// 			return (abs_path);
// 		}
// 		abs_path = path_tail;
// 		abs_path++;
// 		path_tail = ft_strchr(abs_path, ':');
// 	}
// 	ft_bzero(f_path, PATH_MAX);
// 	strncpy(f_path, abs_path, sizeof(f_path) - 1);
// 	ft_strlcat(f_path, "/", sizeof(f_path));
// 	ft_strlcat(f_path, line, sizeof(f_path));
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

char	**subsequent_argv_recursive(t_token *token, int nargs, char **argv)
{
	if (token == NULL || token->kind == TK_EOF)
		return (argv);
	argv = realloc(argv, (nargs + 2) * sizeof(char *));
	argv[nargs] = ft_strdup(token->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (subsequent_argv_recursive(token->next, nargs + 1, argv));
}

char	**token_to_argv(t_token *tok)
{
	char	**argv;

	argv = (char **)ft_calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (subsequent_argv_recursive(tok, 0, argv));
}
