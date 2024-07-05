#include "readline.h"

extern char	**environ;


int main(void)
{
	int i;

	i=0;
	while(environ[i])
	{
		printf("%s\n",environ[i]);
		i++;
	}
	return 0;
}

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
