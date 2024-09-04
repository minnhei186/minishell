/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:59:51 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/30 03:19:11 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"
#include	"../libft/libft.h"

/*
   Pipelines
	   A pipeline is a sequence of one or more commands separated by the
	   character |.  The format for a pipeline is:

	   [time [-p]] [ ! ] command [ | command2 ... ]

	   The standard output of command is connected via a pipe to the standard
	   input of command2.  This connection is performed before any redirections
	   specified by the command (see REDIRECTION below).

	   The return status of a pipeline is the exit status of the last command,
	   unless the pipefail option is enabled.  If pipefail is enabled, the
	   pipeline's return status is the value of the last (rightmost) command to
	   exit with a non-zero status, or zero if all commands exit successfully.
	   If the reserved word !  precedes a pipeline, the exit status of that
	   pipeline is the logical negation of the exit status as described above.
	   The shell waits for all commands in the pipeline to terminate before
	   returning a value.

	   If the time reserved word precedes a pipeline, the elapsed as well as
	   user and system time consumed by its execution are reported when the
	   pipeline terminates.  The -p option changes the output format to that
	   specified by POSIX.  The TIMEFORMAT variable may be set to a format
	   string that specifies how the timing information should be displayed;
	   see the description of TIMEFORMAT under Shell Variables below.

	   Each command in a pipeline is executed as a separate process (i.e., in a
	   subshell).
*/
t_node	*pipe_line(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_PIPE_LINE);
	node->in_pipe[0] = STDIN_FILENO;
	node->in_pipe[1] = -1;
	node->out_pipe[0] = -1;
	node->out_pipe[1] = STDOUT_FILENO;
	node->cmd = simple_command(&token, token);
	// if (node->cmd == NULL)
	// {
	// 	free_node(node);
	// 	*rest = NULL;
	// 	return (NULL);
	// }
	if (equal_op(token, "|"))
		node->next = pipe_line(&token, token->next);
	*rest = token;
	return (node);
}

/*
	control operator
	A token that performs a control function.  It is one of the following symbols:
	|| & && ; ;; ( ) | <newline>
*/
bool	is_control_operator(t_token *token)
{
	static char *const	operators[] = {\
		"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (operators_cmp(token->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
   	Simple Commands
	A simple command is a sequence of optional variable assignments followed
	by blank-separated words and redirections, and terminated by a control
	operator.  The first word specifies the command to be executed, and is
	passed as argument zero.  The remaining words are passed as arguments to
	the invoked command.

	The return value of a simple command is its exit status, or 128+n if the
	command is terminated by signal n.
*/

t_node	*simple_command(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &token, token);
	//debug
	// printf("pass2\n");
	//end
	while (token && !at_eof(token) && !is_control_operator(token))
	{
		// printf("pass3\n");
		append_command_element(node, &token, token);
		// if (token == NULL)
		// {
		// 	ft_putstr_fd("minishell: syntax error\n", 2);
		// 	// fprintf(stderr, "minishell: syntax error\n");
		// 	free_node(node);
		// 	*rest = NULL;
		// 	return (NULL);
		// }
	}
	*rest = token;
	return (node);
}
