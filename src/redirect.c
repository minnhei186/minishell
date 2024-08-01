/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:54:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 18:44:30 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../include/readline.h"

// void	redirect(int targetfd, char *filename)
// {
// 	int filefd;
// 	int	stashed_targetfd;

// 	filefd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	filefd = stashfd(filefd);

// 	stashed_targetfd = stashfd(targetfd);
// 	if (filefd != targetfd)
// 	{
// 		dup2(filefd, targetfd);
// 		close(filefd);
// 	}

// 	exec_command();
// 	dup2(stashed_targetfd, targetfd);
// }

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

int	open_redir_file(t_node *node)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPE_LINE)
	{
		if (open_redir_file(node->cmd) < 0)
			return (-1);
		if (open_redir_file(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects));
	else if (node->kind == ND_REDIR_OUT)
		node->file_fd = open(node->file_name->word, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->file_fd = open(node->file_name->word, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
		node->file_fd = open(node->file_name->word, \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_HEREDOC)
		node->file_fd = read_heredoc(node->delimiter->word);
	else
		assert_error("open_redir_file");
	if (node->file_fd < 0)
	{
		xperror(node->file_name->word);
		return (-1);
	}
	node->file_fd = stashfd(node->file_fd);
	return (open_redir_file(node->next));
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (is_redirect(redir))
	{
		redir->stashed_target_fd = stashfd(redir->target_fd);
		dup2(redir->file_fd, redir->target_fd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}

// Reset must be done from tail to head
void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (is_redirect(redir))
	{
		close(redir->file_fd);
		close(redir->target_fd);
		dup2(redir->stashed_target_fd, redir->target_fd);
	}
	else
		assert_error("reset_redirect");
}
