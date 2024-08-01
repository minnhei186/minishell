#include "process.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


static int	idata = 111;
extern char **environ;

void	errExit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}


void	child_f(void)
{
	char	*argv[2];

	printf("now child function do...\n");
	argv[0] = "/bin/ls";
	argv[1] = NULL;
	execve(argv[0], argv, environ);
}

int	main(void)
{
	int		istack;
	int		status;
	pid_t	childPid;

	istack = 222;
	status = -1;
	switch (childPid = fork())
	{
	case -1:
		errExit("fork");
	case 0:
		child_f();
		idata *= 3;
		istack *= 3;
		break ;
	default:
		//	wait(&status);
		break ;
	}
	printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
			(childPid == 0) ? "child" : "(parent)", idata, istack);
	printf("now    case value: %i   status value:%i\n", childPid, status);
	exit(EXIT_SUCCESS);
}
