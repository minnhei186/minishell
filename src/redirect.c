/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:54:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/24 20:45:12 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../include/readline.h"

bool	g_readline_interrupted;
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

int	read_heredoc(const char *delimiter, bool is_deli_unquoted, t_status *status)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	g_readline_interrupted = false;
	line = readline("> ");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_readline_interrupted || \
			ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_deli_unquoted)
			line = expand_heredoc_line(line, status);
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

// int	read_heredoc(const char *delimiter, bool is_deli_unquoted)
// {
// 	char	*line;
// 	int		pfd[2];

// 	if (pipe(pfd) < 0)
// 		fatal_error("pipe");
// 	g_readline_interrupted = false;
// 	line = readline("> ");
// 	while (line && !g_readline_interrupted)
// 	{
// 		if (ft_strcmp(line, delimiter) == 0)
// 			break ;
// 		if (is_deli_unquoted)
// 			line = expand_heredoc_line(line);
// 		dprintf(pfd[1], "%s\n", line);
// 		free(line);
// 		line = readline("> ");
// 	}
// 	free(line);
// 	close(pfd[1]);
// 	return (pfd[0]);
// }

// int	read_heredoc(const char *delimiter, bool is_deli_unquoted)
// {
// 	char	*line;
// 	int		pfd[2];

// 	if (pipe(pfd) < 0)
// 		fatal_error("pipe");
// 	g_readline_interrupted = false;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 			break ;
// 		if (g_readline_interrupted)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (is_deli_unquoted)
// 			line = expand_heredoc_line(line);
// 		dprintf(pfd[1], "%s\n", line);
// 		free(line);
// 	}
// 	close(pfd[1]);
// 	return (pfd[0]);
// }

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
