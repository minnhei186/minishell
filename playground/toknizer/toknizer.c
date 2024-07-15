#include <stdlib.h>
#include <string.h>

enum						e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind	t_token_kind;

typedef struct s_token		t_token;

struct						s_token
{
	t_token_kind			kind;
	char					*position;
	t_token					*next;
};

bool is_blank(char c)
{
	return (c==' '|| c=='\t' ||c=='\n');
}


//metaは飛ばす
//*inputの格納庫のアドレスである、今変えたのは
//*inputの中のアドレスの値を変えた
//inputから見ると同じ格納庫を見ているしかし、その格納庫の中身は変わっている


bool is_metacharacter(char c)
{
	return (c&&strchr("|&;*()<>\t\n",c));
}

bool is_word(char *s)
{
	return (*s&& !is_metacharacter(*s));
}

t_token *word(t_token *current,char **input_p)
{
	char *word;
	char *input_head;

	input_head=*input_p;
	
	if((**input_p)&&!is_metacharacter(**input_p))
		(*input_p)++;
	word=strndup(start,line-start);
	if(!word)
		fatal_error("strdup");
	
	return (new_token(word,TK_WORD,current));
}




//トークンに文字列を新たに作成して保存しよう
t_token	*tokenizer(char *input_p)
{
	//最初のheadはローカル変数として作成
	// headの露出、概念場と形と露出
	t_token	*currnt;
	t_token head; 

	current = &head;
	while (*input_p)
	{
		while (is_blank(*input_p))
			input_p++;

		if(is_op(*input_p))
			currnt=operator(currnt,&input_p);
		else if(is_str(*input_p))
			currnt=word(currnt,&input_p);
		else
			assert_error("Unexpected Token");
	}


	make_and_link_token(TK_EOF, current, input_p);

	return (head.next);
}


//t_token	*make_and_link_token(t_token_kind kind, t_token *currnt, char **input_p)
//{
//	t_token	*new_toknen;
//
//	//new_token = (t_token *)calloc(sizeof(t_token), 1);
//	//if(new_token==NULL)
//	//	fatal_error("calloc");
//	
//	if(kind==TK_WORD)
//	{
//		word=
//	}
//	else if(kind==TK_OP)
//	{
//	}
//	else if(kind==TK_EOF)
//	{
//	}
//
//	new_token->kind = kind;
//	new_token->position = input_p;
//	currnt->next = new_token;
//	return (new_token);
//}
//
//
