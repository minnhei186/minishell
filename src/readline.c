/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:31:37 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/28 23:51:11 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../include/error.h"
#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<errno.h>

void	initenv(t_map **map);
pid_t	exec_pipeline(t_node *node, t_status *status);
int		wait_pipeline(pid_t last_pid);
int		exec(t_node *node, t_status *last_status);
void	interpreter(char *line, int *state_loca, t_status *status);

void	validate_access(const char *path, const char *file_name)
{
	if (path == NULL && access(path, F_OK) < 0)
	{
		if (ft_strchr(file_name, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			perror(file_name);
		}
		else
			error_exit(file_name, "command not found", 127);
	}
}

int	main(void)
{
	char		*line;
	t_status	status;

	initenv(&status.env_map);
	status.last_status = 0;
	status.syntax_error = false;
	rl_outstream = stderr;
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpreter(line, &status.last_status, &status);
		free(line);
	}
	exit(status.last_status);
}
