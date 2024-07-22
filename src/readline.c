/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:31:37 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/23 00:06:19 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"
#include	"error.h"
#include	"../libft/libft.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

// char	*search_path(const char *file_name)
// {
// 	char	path[PATH_MAX];
// 	char	*value;
// 	char	*end;
// 	char	*dup;

// 	value = getenv("PATH");
// 	while (*value)
// 	{
// 		bzero(path, PATH_MAX);
// 		end = ft_strchr(value, ':');
// 		if (end)
// 			strncpy(path, value, end - value);
// 		else
// 			strlcpy(path, value, PATH_MAX);
// 		strlcat(path, "/", PATH_MAX);
// 		strlcat(path, file_name, PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			dup = strdup(path);
// 			if (dup == NULL)
// 				fatal_error("strdup");
// 			return (dup);
// 		}
// 		if (end == NULL)
// 			return (NULL);
// 		value = end + 1;
// 	}
// 	return (NULL);
// }

void	validate_access(const char *path, const char *file_name)
{
	if (path == NULL)
		error_exit(file_name, "command not found", 127);
	if (access(path, F_OK) < 0)
		error_exit(file_name, "command not found", 127);
}

int	exec(char *argv[])
{
	extern char		**environ;
	const char		*path = argv[0];
	pid_t			pid;
	int				wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (ft_strchr(path, '/') == NULL)
			path = find_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

/*
	@param
	*line -> Get the current line
	*state_loca -> State location
*/
void	interpreter(char *line, int *state_loca)
{
	t_token	*token;
	char	**argv;
	t_node	*node;
	bool	syntax_error;

	syntax_error = false;
	token = tokenizer(line);
	if (token->kind == TK_EOF)
		;
	else if (syntax_error)
		*state_loca = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		expand(node);
		argv = token_to_argv(node->args);
		*state_loca = exec(argv);
		free_argv(argv);
		free_node(node);
	}
	free_token(token);
}

int	main(void)
{
	char	*line;
	int		status;

	status = 0;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpreter(line, &status);
		free(line);
	}
	exit(status);
}
