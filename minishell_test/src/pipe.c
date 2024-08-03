/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:57:27 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/01 16:58:31 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"
#include	"../libft/libft.h"

static void	cpy_pipe(int dst[2], int src[2]);

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->out_pipe) < 0)
		fatal_error("pipe");
	cpy_pipe(node->next->in_pipe, node->out_pipe);
}

void	prepare_pipe_child(t_node *node)
{
	close(node->out_pipe[0]);
	dup2(node->in_pipe[0], STDIN_FILENO);
	if (node->in_pipe[0] != STDIN_FILENO)
		close(node->in_pipe[0]);
	dup2(node->out_pipe[1], STDOUT_FILENO);
	if (node->out_pipe[1] != STDOUT_FILENO)
		close(node->out_pipe[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->in_pipe[0] != STDIN_FILENO)
		close(node->in_pipe[0]);
	if (node->next)
		close(node->out_pipe[1]);
}

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}
