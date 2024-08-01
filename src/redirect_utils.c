/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:46:11 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 19:46:51 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../include/readline.h"

bool	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (true);
	else if (node->kind == ND_REDIR_IN)
		return (true);
	else if (node->kind == ND_REDIR_APPEND)
		return (true);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (true);
	return (false);
}

static int	open_redir_file_helper(t_node *node)
{
	int	fd;

	if (node->kind == ND_REDIR_OUT)
		fd = open(node->file_name->word, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		fd = open(node->file_name->word, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
		fd = open(node->file_name->word, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_HEREDOC)
		fd = read_heredoc(node->delimiter->word);
	else
		assert_error("open_redir_file");
	return (fd);
}

int	open_redir_file(t_node *node)
{
	int	fd;

	if (!node)
		return (0);
	if (node->kind == ND_PIPE_LINE)
	{
		if (open_redir_file(node->cmd) < 0 || open_redir_file(node->next) < 0)
			return (-1);
		return (0);
	}
	if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects));
	fd = open_redir_file_helper(node);
	if (fd < 0)
	{
		xperror(node->file_name->word);
		return (-1);
	}
	node->file_fd = stashfd(fd);
	return (open_redir_file(node->next));
}
