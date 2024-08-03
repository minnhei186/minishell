/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:49:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 20:00:13 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"
#include	"../include/error.h"
#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<errno.h>

void	validate_access(const char *path, const char *file_name);

// pid_t	exec_pipeline(t_node *node)
// {
// 	extern char		**environ;
// 	char			*path;
// 	pid_t			pid;
// 	char			**argv;

// 	if (node == NULL)
// 		return (-1);
// 	prepare_pipe(node);
// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		prepare_pipe_child(node);
// 		do_redirect(node->cmd->redirects);
// 		argv = token_to_argv(node->cmd->args);
// 		path = argv[0];
// 		if (ft_strchr(path, '/') == NULL)
// 			path = find_path(path);
// 		validate_access(path, argv[0]);
// 		execve(path, argv, environ);
// 		reset_redirect(node->cmd->redirects);
// 		fatal_error("execve");
// 	}
// 	prepare_pipe_parent(node);
// 	if (node->next)
// 		return (exec_pipeline(node->next));
// 	return (pid);
// }

void	setup_child_process(t_node *node)
{
	extern char	**environ;
	char		*path;
	char		**argv;

	prepare_pipe_child(node);
	do_redirect(node->cmd->redirects);
	argv = token_to_argv(node->cmd->args);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = find_path(path);
	validate_access(path, argv[0]);
	execve(path, argv, environ);
	reset_redirect(node->cmd->redirects);
	fatal_error("execve");
}

pid_t	exec_pipeline(t_node *node)
{
	pid_t	pid;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
		setup_child_process(node);
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			status = WEXITSTATUS(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}

int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	if (open_redir_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}

void	interpreter(char *line, int *state_loca)
{
	t_token	*token;
	t_node	*node;
	bool	syntax_error;

	syntax_error = false;
	token = tokenizer(line);
	if (at_eof(token))
		;
	else if (syntax_error)
		*state_loca = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		if (syntax_error)
			*state_loca = ERROR_PARSE;
		else
		{
			expand(node);
			*state_loca = exec(node);
		}
		free_node(node);
	}
	free_token(token);
}
