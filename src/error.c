/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:45:06 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/15 23:38:41 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
*/

static void	perror_prefix(void)
{
	dprintf(STDDER_FILENO, "%s", ERROR_PREFIX);
}

void	assert_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/* Fatal Error */
void	fatal_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}
