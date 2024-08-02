#include "minishell.h"

int	equal_path(char *path1, char *path2)
{
	struct stat	path_info1;
	struct stat	path_info2;
	int			equal_check;

	//構造体を初期化
	memset(&path_info1, 0, sizeof(st1));
	memset(&path_info2, 0, sizeof(st2));
	// pathの情報を取得
	if (stat(path1, &path_info1) < 0)
		fatal_error("stat");
	if (stat(path2, &path_info2) < 0)
		fatal_error("stat");
	equal_check = (path_info1.st_ino == path_info2.st_ino);
	return (equal_check);
}

int	builtin_pwd(void)
{
	char	*environ_path;
	char	cd_path[PATH_MAX];

	environ_path = xgetenv("PWD");
	//環境変数が取得できなかった場合か？
	if (environ_path == NULL || equal_path(environ_pwd, ".") == 0)
	{
		if (getcwd(cd_path, PATH_MAX) == NULL)
		{
			builtin_error("pwd", NULL, "getcwd");
			return (1);
		}
		write(STDOUT_FILENO, cd_path, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		write(STDOUT_FILENO, environ_path, strlen(environ_path));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
}
