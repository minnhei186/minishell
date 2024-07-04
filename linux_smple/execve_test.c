#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>


extern char **environ;

//int main(void)
//{
//	char *argv[2];
//
//	argv[0]="/bin/ls";
//	argv[1]=NULL;
//
//	execve(argv[0],argv,environ);
//
//	return 0;
//}


int main(void)
{
	char *argv[2];

	argv[0]="/bin/ls";
	argv[1]=NULL;

	system(argv[0]);

	return 0;
}
