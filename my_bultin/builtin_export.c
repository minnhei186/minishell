#include "minishell"

void	f_env(void)
{
	t_item	*current;

	current = envmap->item_head.next;
	while (current)
	{
		if (current->valule)
			ft_printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else 
			printf("declare -x %s\n", current->name);

		current = current->next;
	}
	ft_printf("_=/usr/bin/env\n");
}

// errorではexitしないことが面白い
// statusによって状態の確認を行うのかな？
int	bultin_export(char **argv)
{
	int	i;
	int	status;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		print_allenv();
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(envmap, argv[i], true) < 0)
		{
			bultin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}
