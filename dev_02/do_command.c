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
	char	*tmp_free;

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
			abs_path = strdup(f_path);
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
		abs_path = strdup(f_path);
		return (abs_path);
	}
	else
	{
		free(tmp_free);
		return (NULL);
	}
}

void	ft_do_command(char *line)
{
	char	*argv[3];
	char	*command_path;
	t_token *token;

	token=tokenizer(line);

	command_path = find_path(token->word);
	if (!command_path)
	{
		perror("commnad not found");
		exit(1);
	}
	argv[0] = command_path;
	argv[1] = token->next->word;
	argv[2]=NULL;
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

	status = -1;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid > 0)
	{
		if (wait(&status) < 0)
		{
			perror("wait");
			exit(1);
		}
	}
	else
		ft_do_command(line);
	return (status);
}
