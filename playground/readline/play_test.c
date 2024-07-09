#include "readline.h"

extern char	**environ;

char	*abs_path_get(void)
{
	char		*path;
	const char	*temp;

	path = NULL;
	temp = getenv("PATH");
	if (temp)
	{
		path = (char *)malloc(strlen(temp) + 1);
		if (!path)
		{
			perror("malloc error");
			exit(1);
		}
		strcpy(path, temp);
	}
	else
	{
		perror("environmental variables not found");
		exit(1);
	}
	return (path);
}

char	*find_path(char *line)
{
	char	*abs_path;
	char	f_path[PATH_MAX];
	char	*path_tail;
	char *tmp_free;


	abs_path = abs_path_get();
	tmp_free = abs_path;
	path_tail = strchr(abs_path, ':');
	while (path_tail)
	{
		bzero(f_path, PATH_MAX);
		strncpy(f_path, abs_path, path_tail - abs_path);
		strlcat(f_path, "/", sizeof(f_path));
		strlcat(f_path, line, sizeof(f_path));
		if (access(f_path, 0) == 0)
		{
			free(tmp_free);
			abs_path=strdup(f_path);
			return (abs_path);
		}
		abs_path = path_tail;
		abs_path++;
		path_tail = strchr(abs_path, ':');
	}
	bzero(f_path, PATH_MAX);
	strncpy(f_path, abs_path, sizeof(f_path) - 1);
	strlcat(f_path, "/", sizeof(f_path));
	strlcat(f_path, line, sizeof(f_path));	
	if (access(f_path, 0) == 0)
	{
		free(tmp_free);
		abs_path=strdup(f_path);
		return (abs_path);
	}
	else
	{
		free(tmp_free);
		return (NULL);
	}
}

int	main(void)
{
	char	*abs_path;

	abs_path = find_path("ls");
	printf("abs_path:%s\n", abs_path);
	return (0);
}
