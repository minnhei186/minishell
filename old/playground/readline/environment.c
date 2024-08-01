#include "readline.h"

extern char	**environ;




char *serch_abs_path(char *command_line)
{
	char *path_environ;
	char abs_path[100];
	
	
	strlcpy(abs_path,command_line,strlen(command_line));
	path_environ=getenv("PATH");
	while(
	strlcat(abs_path,path

		

//int main(void)
//{
//	int i;
//
//	i=0;
//	while(environ[i])
//	{
//		printf("%s\n",environ[i]);
//		i++;
//	}
//	return 0;
//}

//int main(void)
//{
//	char *environ;
//
//
//	environ=getenv("HOME");
//
//
//	printf("environment:%s\n",environ);
//	return 0;
//}
