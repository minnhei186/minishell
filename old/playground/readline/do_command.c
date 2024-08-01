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

//abs_getはfreeすること
//コロンが存在しない場合もあるよ//NULL
//tailがあることでstrncpyが必ずそれ以下になることが保証されている
//cat操作でPATH_MAXを超える可能性がある
//strlenでコマンドの全ての長さを測りMAXを超えないか考えよう
//今はとりあえず良い
//そうか、エラー処理するのではなくそのような文字列を作成すればいい
//そうかそうか、独立した関数においてそのような状況を許容するような
//acitiveな関数を作成することによって前提が必要なくなる、
//sizeofは終端文字分の個数であるよって、終端文字にアクセスしたいなら[sizeof(s)-1]となる

char	find_path(char *line)
{
	char	*abs_path;
	char	f_path[PATH_MAX];
	char	path_tail;
	char *tmp_free;

	abs_path = abs_path_get();
	tmp_free=abs_path;
	path_tail = strchr(abs_path, ':');
	while (path_tail)
	{
		bzero(f_path, PATH_MAX);
		strncpy(f_path, abs_path, tail - abs_path); //終端文字はコピーされない 個数分（:不必
		strlcat(f_path, "/", sizeof(f_path));
		strlcat(f_path, line, sizeof(f_path));
		if(access(f_path,0)==0)
		{
			free(abs_path);
			return f_path;
		}
		abs_path=path_tail++;
		path_tail=strchr(abs_path,':');	
	}
	bzero(f_path,PATH_MAX);
	strncpy(f_path,abs_path,sizeof(f_path)-1);
	strlcat(f_path,"/",sizeof(f_path));
	strlcat(f_path,line,sizeof(f_pat));

	if(access(f_path,0)==0)
	{
		free(abs_path);
		return f_path;
	}
	else
	{
		free(abs_path);
		return NULL;
	}
}


	

void	ft_do_command(char *line)
{
	char	*argv[2];

	argv[0] = line;
	argv[1] = NULL;
	if (find_path(line) == -1)
	{
		perror("commnad not found");
		exit(1);
	}
	//exe_command
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
	//	printf("fork_pid:%i\n",pid);
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
