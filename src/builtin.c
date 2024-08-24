/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:37:38 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 04:58:07 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/readline.h"

int	exec_builtin(t_node *node, t_status *last_status, t_map *envmap)
{
	int		status;
	char	**argv;

	do_redirect(node->cmd->redirects);
	argv = token_to_argv(node->cmd->args);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv, last_status);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, envmap);
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->cmd->redirects);
	return (status);
}

t_cmd	get_builtin_enum(const char *cmd_name)
{
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (B_EXIT);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (B_EXPORT);
	return (B_UNKNOWN);
}

// char *builtin_commands[] = {"exit"};
bool	is_builtin(t_node *node)
{
	const char		*cmd_name;

	if (node == NULL || node->cmd == NULL || node->cmd->args == NULL ||\
		node->cmd->args->word == NULL)
		return (false);
	cmd_name = node->cmd->args->word;
	return (get_builtin_enum(cmd_name) != B_UNKNOWN);
	// i = 0;
	// while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	// {
	// 	if (ft_strcmp(cmd_name, builtin_commands[i]) == 0)
	// 		return (true);
	// 	i++;
	// }
	// return (false);
}
