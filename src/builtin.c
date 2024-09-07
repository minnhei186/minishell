/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:37:38 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/07 21:29:34 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include <sys/wait.h>

int	exec_builtin(t_node *node, t_status *p_status)
{
	int		status;
	char	**argv;

	do_redirect(node->cmd->redirects);
	argv = token_to_argv(node->cmd->args);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv, p_status);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, p_status->env_map);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv, p_status->env_map);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv, p_status->env_map);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv, p_status->env_map);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv);
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
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (B_UNSET);
	// if (ft_strcmp(cmd_name, "env") == 0)
	// 	return (B_ENV);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (B_CD);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (B_ECHO);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (B_PWD);
	return (B_UNKNOWN);
}

// char *builtin_commands[] = {"exit"};
bool	is_builtin(t_node *node)
{
	const char		*cmd_name;

	if (node == NULL || node->cmd == NULL || node->cmd->args == NULL || \
		node->cmd->args->word == NULL)
		return (false);
	cmd_name = node->cmd->args->word;
	return (get_builtin_enum(cmd_name) != B_UNKNOWN);
}
