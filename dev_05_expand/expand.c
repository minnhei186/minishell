#include "readline.h"
#include <string.h>

void append_char(char **str_pp,char c)
{
	size_t size;
	char *new;

	size=2;
	if(*str_pp)
		size+=strlen(*str_pp);
	new=malloc(size);
	if(new==NULL)
		fatal_error("malloc");
	if(*str_pp)
		strlcpy(new,*str_pp,size);
	new[size-2]=c;
	new[size-1]='\0';
	if(*str_pp)
		free(*str_pp);
	*str_pp=new;
}



void quote_removal(t_token *tok)
{
	char *new_word;
	char *old_word;

	int q;
	q=0;
	int i;
	i=0;


	if(tok==NULL||tok->kind!=TK_WORD||tok->word==NULL)
		return ;
	old_word=tok->word;
	new_word=NULL;
	while((*old_word)&&!is_metacharacter(*old_word))//!!になってる！！
	{
		//printf("c:%c\n",*old_word);
		if(*old_word==SINGLE_QUOTE_CHAR)
		{
			old_word++;
			while(*old_word!=SINGLE_QUOTE_CHAR)
			{
				if(*old_word=='\0')
					printf("unclosed single quote");
			append_char(&new_word,*old_word);
			old_word++;
		//	printf("q:%i\n",q++);
			}
			old_word++;
		}
		else
		{
			append_char(&new_word,*old_word);
				old_word++;
		//	printf("i:%i\n",i++);
		}
	}


	free(tok->word);
	tok->word=new_word;
//	printf("new_word:%s\n",new_word);
	quote_removal(tok->next);
}

			



void expand (t_token *tok)
{
	quote_removal(tok);
}

