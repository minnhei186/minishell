/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:45:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/30 01:03:55 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

/* 
	Assertion Error

	1. sprintf()
	sprintf()は、フォーマットされたデータを文字列として返し、
	ユーザはそれを保存したり、適切な操作や表示を行うことができる。

	2. fwrite()
	fwrite()への言及も見たことがあるかもしれない。
	fprintf(fid,...)は(この目的では)fwrite(fid,sprintf(...))と同じだが、
	fprintf()は接続されたデバイスに書き出す前に文字列全体を構築する必要は(理論的には)ない。
	
	3. fprintf()
	fprintf()はsprintfとfwriteの組み合わせの利便性と考えることもできるが、
	持つ価値があるほど頻繁に使用される利便性である。

	<assert_error code by Hosokaw>
	perror_prefix();
	fprintf(stderr, "Error: %s\n", message);
*/

void	perror_prefix(void);
// bool	*get_syntax_error_ptr(void);

//	exit(EXIT_FAILURE);
void	assert_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

/* Fatal Error */
void	fatal_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

/* Leave from the error */
void	error_exit(const char *l, const char *msg, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s\n", l, msg);
	exit(status);
}

void	tokenize_error(const char *l, char **rest, char *line, \
	t_status *status)
{
	status->syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, \
		"syntax error near unexpected character `%c' in %s\n", *line, l);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(t_token **rest, t_token *token)
{
	perror_prefix();
	dprintf(STDERR_FILENO,
		"syntax error near unexpected token `%s'\n", token->word);
	while (token && !at_eof(token))
		token = token->next;
	*rest = token;
}
