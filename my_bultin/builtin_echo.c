#include "minishell.h"

int	builtin_echo(char **argv)
{
	int		need_newline;
	int		first_flag;
	size_t	i;

	i = 1;
	if (argv[i])
	{
		if (strncmp(argv[i], "-n", 2) == 0)
		{
			i++;
			need_newline = 0;
		}
		need_newline = 0;
	}
	//オプションがある場合は表示しない（しかしi++しているので）
	//一番最初の引数でないのならスペースが必要
	first_flag = 1;
	while (argv[i])
	{
		if (first_flag != 1)
			write(STDOUT_FILENO, " ", 1);
		first_flag = 0;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (need_newline == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
