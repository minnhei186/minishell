#include "minishell.h"

int builtin_env(void)
{
	t_item *current;
	int status;
	status=0;

	current=envmap->item_head.next;
	//空のheadを連結リストの頭にしてリストを作成している
	while(current)
	{
		if(current->valule)
			ft_printf("%s=%s\n",current->name,current->value);
		current=current->next;
	}
	ft_printf("_=/usr/bin/env\n");
	return status;
}
