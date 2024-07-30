/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:54:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/31 00:05:18 by geonwkim         ###   ########.fr       */
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

int	open_redir_file(t_node *redir)
{
	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_OUT)
		redir->file_fd = open(redir->file_name->word, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->kind == ND_REDIR_IN)
		redir->file_fd = open(redir->file_name->word, O_RDONLY);
	else if (redir->kind == ND_REDIR_APPEND)
		redir->file_fd = open(redir->file_name->word, \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->kind == ND_REDIR_HEREDOC)
		redir->file_fd = read_heredoc(redir->delimiter->word);
	else
		assert_error("open_redir_file");
	if (redir->file_fd < 0)
	{
		xperror(redir->file_name->word);
		return (-1);
	}
	redir->file_fd = stashfd(redir->file_fd);
	return (open_redir_file(redir->next));
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
