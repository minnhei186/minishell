/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:42:00 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/10 22:14:13 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<errno.h>

void	handle_exec_error(char *cmd, char *path)
{
	if (cmd == NULL)
		return ;
	if (ft_strchr(cmd, '/'))
		perror(cmd);
	else if (path != NULL)
		error_exit(cmd, "No such file or directory", 127);
	else
		error_exit(cmd, "command not found", 127);
}

void	print_env_item(t_item *cur)
{
	if (cur->value)
		printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
	else
		printf("declare -x %s\n", cur->name);
}

void	print_env_for_name(t_map *envmap, char *env_name)
{
	t_item	*cur;

	cur = envmap->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, env_name) == 0)
		{
			print_env_item(cur);
			break ;
		}
		cur = cur->next;
	}
}
