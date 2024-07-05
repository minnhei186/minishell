#include "readline.h"

extern char	**environ;

void	ft_do_command(char *line)
{

	char	*argv[2];

	argv[0] = line;
	argv[1] = NULL;
	if (execve(argv[0], argv, environ) < 0)
	{
		perror("execve");
		exit(1);
	}
}

int	ft_mlt_process(char *line)
{

	int	pid;
	int	status;

	status=-1;


	pid = fork();
//	printf("fork_pid:%i\n",pid);

	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid >0)
	{
		if (wait(&status) < 0)
		{
			perror("wait");
			exit(1);
		}
	}
	else
		ft_do_command(line);


	return status;
}
