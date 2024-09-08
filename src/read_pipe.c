/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:49:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/08 21:57:51 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<errno.h>

void	validate_access(const char *path, const char *file_name);
void	handle_exec_error(char *cmd, char *path);

// if (ft_strchr(path, '/') == NULL)
// Check if that PATH is UNSET
// argv[0] == NULL - exit(1)
// -> If >>>> (Redirection) is coming, should return without any Memory leaks
void	setup_child_process(t_node *node, t_status *status)
{
	char	*path;
	char	**argv;

	reset_signal();
	prepare_pipe_child(node);
	if (is_builtin(node))
		exit(exec_builtin(node, status));
	do_redirect(node->cmd->redirects);
	argv = token_to_argv(node->cmd->args);
	if (!argv[0])
		exit(1);
	if (ft_strchr(argv[0], '/'))
		path = argv[0];
	else
		path = find_path(argv[0], status);
	execve(path, argv, get_environ(status->env_map));
	handle_exec_error(argv[0], path);
	free_argv(argv);
	exit(1);
}

pid_t	exec_pipeline(t_node *node, t_status *status)
{
	pid_t	pid;

	if (node == NULL)
	{
		free(node);
		return (-1);
	}
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		setup_child_process(node, status);
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next, status));
	return (pid);
}

/*
	1. Wait for a Child Process
		status = WEXITSTATUS(wstatus);

	2. Check if the Process was Terminated by a Signal
		if (WIFSIGNALED(wstatus))
			status = 128 + WTERMSIG(wstatus);
		else
			status = WEXITSTATUS(wstatus);
	
	3. Handle Errors from `wait()`
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break;
			else if (errno == EINTR)
				continue;
			else
				fatal_error("wait");
		}

	このコードは、子プロセスの終了を待つプロセス管理ルーチンの一部である。
	
	子プロセスが正常に終了したか、シグナルによって強制終了されたかをチェックし、
	wait()でさまざまなエラー・ケースを処理する。
*/
int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

int	exec(t_node *node, t_status *last_status)
{
	pid_t	last_pid;
	int		status;

	if (open_redir_file(node, last_status) < 0)
		return (ERROR_OPEN_REDIR);
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node, last_status);
	else
	{
		last_pid = exec_pipeline(node, last_status);
		status = wait_pipeline(last_pid);
	}
	return (status);
}

// (!node) -> Error handling for failed parsing
void	interpreter(char *line, int *state_loca, t_status *status)
{
	t_token	*token;
	t_node	*node;

	token = tokenizer(line, status);
	if (at_eof(token))
		;
	else if (status->syntax_error)
		*state_loca = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		if (status->syntax_error)
			*state_loca = ERROR_PARSE;
		else
		{
			expand(node, status);
			*state_loca = exec(node, status);
		}
		free_node(node);
	}
	free_token(token);
}
