/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:46:11 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 19:01:56 by geonwkim         ###   ########.fr       */
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

static int	open_file(t_node *node, int flags, mode_t mode)
{
	node->file_fd = open(node->file_name->word, flags, mode);
	if (node->file_fd < 0)
	{
		xperror(node->file_name->word);
		return (-1);
	}
	node->file_fd = stashfd(node->file_fd);
	return (0);
}

int	open_redir_file(t_node *node)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPE_LINE)
		return ((open_redir_file(node->cmd) < 0) ||
				(open_redir_file(node->next) < 0));
	if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects));
	if (node->kind == ND_REDIR_OUT)
		return (open_file(node, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (node->kind == ND_REDIR_IN)
		return (open_file(node, O_RDONLY, 0));
	if (node->kind == ND_REDIR_APPEND)
		return (open_file(node, O_CREAT | O_WRONLY | O_APPEND, 0644));
	if (node->kind == ND_REDIR_HEREDOC)
	{
		node->file_fd = read_heredoc(node->delimiter->word);
		if (node->file_fd < 0)
			return (-1);
		node->file_fd = stashfd(node->file_fd);
	}
	return (open_redir_file(node->next));
}
