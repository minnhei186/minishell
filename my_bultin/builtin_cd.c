#include "minishell"

//ここで先の疑問に答える処理が行われている
// oldとnewで環境変数を入れ替える（処理を行う）
//なるほどね、ここで得たargvのディレクトリに変更するのか
//
// envmap、環境変数からこれらを取得できるのだろうか?

static int	ft_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

//このダブルポインタはあくまでもポインタが保持するアドレスを動かすよう
int consume_path(char **current_path,char *path_unit) 
{
	//.はひとつしかない（どのくらい動かすか）(pathをずらしたい）
	size_t path_unit_len;

	path_unit_len=strlen(path_unit);

	if(strncmp(**current_path,path_unit,path_unit_len)==0)//指定したpath_unitと今見ているpathのunitが等しい時
	{
		//cd ./ . このような仕様による　cd .42tokyo/..2e2などは許されていない
		if(path[path_unit_len]=='\0'||path[path_unit_len]=='/')
		{
			(*current_path)=(*current_path)+path_unit_len;
			return 1;
		}
	}
		return 0;
}


//consume_pathと
//newpwdはみていることが異なる
//consume_pathではもう次に行っている

//
void consume_and_append_path(char *new_pwd,char **path)
{
	size_t path_unit_len;

	path_unit_len=0;
	while(*path[path_unit_len]!='\0'&&*path[path_unit_len]!='/')
		path_unit_len++;

	//new_pwdの終端に/がなかったら/をつけてからcat
	if(new_pwd[strlen[new_pwd]-1]!='/')
		strcat(new_pwd,"/");
	strncat(new_pwd,*path,path_unit_len);
	*path=*path+path_unit_len;
}

			

void delete_last_unit(char *new_pwd)
{
	char *head;
	char *tail_slash;
	int i;

	head=new_pwd;
	tail=NULL;

	i=0;
	while(path[i])
	{
		if(path[i]=='/')
			tail_slash=&path[i];
		i++;
	}
	//rootは常に残し続ける必要がある（どんなに戻っても残るため）
	if(tail_slash!=head)
		tail_slash[i]='\0';
}







//最後はdupで動的に確保してメモリを使用可能状態にする
char *make_absolute_new_pwd(char *old_pwd,char *path)
{
	char new_pwd[PATH_MAX];
	char *dup;
	int i;

	i=0;
	if(old_pwd==NULL)
		return NULL;
	//ルートディレクトリから始まるなら、相対パス出ないのでold_pwdはいらない
	if(path[i]=='/')
			strlcpy(new_pwd,"/",PATH_MAX);
	else
		strlcpy(new_pwd,old_pwd,PATH_MAX);


	//これでnew_pwdがpath以外作成できた	
	while(path[i])
	{
		if(path[i]=='/')
			i++;
		//なるほど、ここではpathに対してアクセスを行う
		//なぜなら、すでにコピーされているため
		else if(consume_path(&path,path,"."));
		else if(consume_path(&path,path,".."))
			delete_last_path(new_pwd);
		else
			consume_and_append_path(new_pwd,&path,path);
	}
	//dupで行うことで必要な分だけ作成することができる
	//いちいち消せないといけなくなるもんな
	dup=ft_strdup(new_pwd);
	if(dup==NULL)
		fatal_error("strdup");
	return dup;
	

int	builtin_cd(char **argv)
{
	char *old_pwd;
	char *new_pwd;
	char *home;
	char *path[PATH_MAX];

	//古いものをセットした
	old_pwd = map_get(envmap, "PWD");
	map_set(envmap, "OLDPWD", old_pwd);

	if (ft_argc(argv) == 1)
	{
		home = map_get(envmap, "HOME");
		if (!home)
		{
			builtin_error("cd", NULL, "HOME not set");
			return (1);
		}
		strlcpy(path, home, PATH_MAX);
	}
	else if (ft_argv(argv) == 2)
		strlcpy(path, argv[1], PATH_MAX);
	else
	{
		fatal_error("cd:too many argment");
		return (1);
	}

	if(chdir(path)<0)
	{
		builtin_error("cd",NULL,"chdir");
		return 1;
	}

	//pathはディレクトリだけであり、絶対パスは示していない(絶対パスを作成)
	new_pwd=make_absolute_new_pwd(old_pwd,path);
	//環境変数を新しいパス、つまりargのディレクトリにパスを変更
	map_set(envmap,"PWD",new_pwd);
	free(new_pwd);
	return 0;
}

