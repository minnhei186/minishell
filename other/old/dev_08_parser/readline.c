#include "readline.h"

int	main(void)
{
	char	*line;
	int status;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		status=ft_mlt_process(line);
		free(line);
	}
	
	exit(0);
}
