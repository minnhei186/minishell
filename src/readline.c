/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:31:37 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/26 17:22:09 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<errno.h>

void	initenv(t_map **envmap);
pid_t	exec_pipeline(t_node *node, t_map *envmap, t_status *status);
int		wait_pipeline(pid_t last_pid);
int		exec(t_node *node, t_map *envmap, t_status *last_status);
void	interpreter(char *line, int *state_loca, \
	t_map *envmap, t_status *status);
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
// 		ft_bzero(path, PATH_MAX);
// 		end = ft_strchr(value, ':');
// 		if (end)
// 			strncpy(path, value, end - value);
// 		else
// 			ft_strlcpy(path, value, PATH_MAX);
// 		ft_strlcat(path, "/", PATH_MAX);
// 		ft_strlcat(path, file_name, PATH_MAX);
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

// int	exec_cmd(t_node *node)
// {
// 	extern char		**environ;
// 	char			*path;
// 	pid_t			pid;
// 	int				wstatus;
// 	char			**argv;

// 	if (node == NULL)
// 		return (-1);
// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		argv = token_to_argv(node->args);
// 		path = argv[0];
// 		if (ft_strchr(path, '/') == NULL)
// 			path = find_path(path);
// 		validate_access(path, argv[0]);
// 		execve(path, argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		wait(&wstatus);
// 		return (WEXITSTATUS(wstatus));
// 	}
// }

// int	exec(t_node *node)
// {
// 	int	status;

// 	if (open_redir_file(node->redirects) < 0)
// 		return (ERROR_OPEN_REDIR);
// 	open_redir_file(node->redirects);
// 	do_redirect(node->redirects);
// 	status = exec_cmd(node);
// 	reset_redirect(node->redirects);
// 	return (status);
// }

// int	exec(char *argv[])
// {
// 	extern char		**environ;
// 	const char		*path = argv[0];
// 	pid_t			pid;
// 	int				wstatus;

// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		if (ft_strchr(path, '/') == NULL)
// 			path = find_path(path);
// 		validate_access(path, argv[0]);
// 		execve(path, argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		wait(&wstatus);
// 		return (WEXITSTATUS(wstatus));
// 	}
// }

/*
	@param
	*line -> Get the current line
	*state_loca -> State location
*/
// void	interpreter(char *line, int *state_loca)
// {
// 	t_token	*token;
// 	char	**argv;
// 	t_node	*node;
// 	bool	syntax_error;

// 	syntax_error = false;
// 	token = tokenizer(line);
// 	if (token->kind == TK_EOF)
// 		;
// 	else if (syntax_error)
// 		*state_loca = ERROR_TOKENIZE;
// 	else
// 	{
// 		node = parse(token);
// 		expand(node);
// 		argv = token_to_argv(node->args);
// 		*state_loca = exec(argv);
// 		free_argv(argv);
// 		free_node(node);
// 	}
// 	free_token(token);
// }

// int		status;
int	main(void)
{
	char		*line;
	t_map		*map;
	t_status	status;

	initenv(&map);
	status.last_status = 0;
	status.syntax_error = false;
	rl_outstream = stderr;
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpreter(line, &status.last_status, map, &status);
		free(line);
	}
	exit(status.last_status);
}
