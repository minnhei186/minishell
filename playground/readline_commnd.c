#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


//lineがから文字のみの場合は履歴には登録せず
int main(void)
{
	char *line;
	rl_outstream=stderr;

	while(1)
	{
		line=readline("minishell$ ");
		if(line==NULL)
			break;
		if(*line)
			add_history(line);
		free(line);
	}
	exit(0);
}

