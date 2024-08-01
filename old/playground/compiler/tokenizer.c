#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tokenのデータ構造は連結リストで定義されており、パーサーは連結リストを追っていくことで入力をすすめる//さらに、これはグローバル変数である。これにより標準入力ストリームのようなイメージで行える

typedef enum
{
	TK_RESERVED,
	TK_NUM,
	TK_EOF,
}						TokenKind;

typedef struct Token	Token;

struct					Token
{
	TokenKind			kind;
	Token				*next;
	int					val;
	char				*str;
};

Token					*token;

bool	consume(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		return (false);
	token = token->next;
	return (true);
}

void	expect(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		printf("%c :ではありません\n", op);
	token = token->next;
}

int	expect_number(void)
{
	int	val;

	if (token->kind != TK_NUM)
	{
		perror("数ではない");
		exit(1);
	}
	val = token->val;
	token = token->next;
	return (val);
}

bool	at_eof(void)
{
	return (token->kind == TK_EOF);
}

//作成することと、繋げることを同じ関数で　空のリストがあることで可能になる
Token	*new_token(TokenKind kind, Token *cur, char *str)
{
	Token	*tok;

	tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return (tok);
}

Token	*tokenize(char *p)
{
	Token	head;
	Token	*cur;

	head.next = NULL;
	cur = &head;
	while (*p)
	{
		while (isspace(*p))
			p++;
		if (*p == '+' || *p == '-')
		{
			cur = new_token(TK_RESERVED, cur, p++);
			continue ;
		}
		if (isdigit(*p))
		{
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue ;
		}
		perror("error");
		exit(1);
	}
	new_token(TK_EOF, cur, p);
	return (head.next);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	token = tokenize(argv[1]);
	while (!at_eof())
	{
		if (consume('+'))
		{
			printf("add rac, %d\n", expect_number());
			continue ;
		}
		expect('-');
		printf(" sub rax,%d\n", expect_number());
	}
	return (0);
}

//while (token->kind != TK_EOF)
//	{
//		printf("%i ", token->val);
//		token = token->next;
//	}

//int main(void)
//{
//	printf("%i\n",token->val);
//	//printf("%i %i %s\n",token->kind,token->val,token->str);
//	return (0);
//}

//Token *symbol_make(char c) {
//	Token *tk;
//	tk=(Token *)malloc(sizeof(Token));
//
//		tk->kind=TK_RESERVED;
//		tk->next=NULL;
//		tk->val=0;
//	if(c=='-')
//		tk->str="-";
//	else if(c=='+')
//		tk->str="+";
//	return (tk);
//}
//
//
//char *get_str_token(char *str)
//{
//	int i;
//	char *tk_str;
//
//	while(str[i]!='\0'&&str[i]!=' ')
//		i++;
//
//	tk_str=(char *)malloc(sizeof(char)*i+1);
//	i=0;
//	while(str[i]!='\0'&&str[i]!=' ')
//	{
//		tk_str[i]=str[i];
//		i++;
//	}
//	tk_str[i]='\0';
//	return (tk_str);
//}
//
//
//
////空白はスキップしている
//Token *make_list(char *str)
//{
//	int i;
//	i=0;
//	if(str[i]=='+'||str[i]=='-')
//		return (symbol_make(str[i]));
//
//	token *tk;
//	tk=(Token *)malloc(sizeof(Toke));
//
//	tk->kind=TK_NUM;
//	tk->next=NULL;
//	tk->val=0;
//	tk->str=get_str_token(str);
//
//	return (tk);
//}

//int main(void)
//{
//	TokenKind kind;
//
//	kind=100;
//
//	printf("%i\n",kind);
//	return (0);
//}
