/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:37:38 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/19 15:59:21 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

int	exec_builtin(t_node *node)
{
	int		status;
	char	**argv;

	do_redirect(node->cmd->redirects);
	argv = token_to_argv(node->cmd->args);
	if (strcmp(argv[0], "exit") == 0)
	{
		status = builtin_exit(argv);
	}
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->cmd->redirects);
	return (status);
}

bool	is_builtin(t_node *node)
{
	const char		*cmd_name;
	char			*builtin_commands[] = {"exit"};
	unsigned int	i;

	if (node == NULL || node->cmd == NULL || node->cmd->args == NULL ||\
			node->cmd->args->word == NULL)
		return (false);
	cmd_name = node->cmd->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
