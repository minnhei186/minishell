#include "minishell.h"
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
	char					*word;
	t_token_kind			kind;
	t_token					*next;
};

t_token *make_token(char *input_str)
{
	
