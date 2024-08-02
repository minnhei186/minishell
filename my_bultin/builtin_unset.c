
#include "minishell.h"

//最後に一つでも削除することができたら、成功とみなしている？
int bultin_unset(char **argv)
{
	int i;
	int status;

	i=0;
	status=0;

	while(argv[i])
		i++;
	if(i==1)
		return (0);

	i=1;
	while(argv[i])
	{
		if(map_unset(envmap,argv[i])<0)
		{
			bultin_error("unset",argv[i],"not a valid identifier");
			status=1;
		}
		else
			status=0;
		i++;
	}

	return status;
}

