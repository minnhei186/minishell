#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

//グローバル変数
// erron
// last_status

// argv[0]は必ずexitが入ってると考える

static long long	digits_process(const char *str, int sign, long long res)
{
	while (ft_isdigit(*str))
	{
		if (res > ((LLONG_MAX - (*str - '0')) / 10))
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

long	ft_strtol(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return ((long)digits_process(str, sign, res) * sign);
}

bool	check_exit_value(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '\0')
		return (false);
	while (value[i])
	{
		if (!isdigit(value[i]))
			return (false);
		i++;
	}
	return (true);
}

int	bultin_exit(char **argv)
{
	int		i;
	long	exit_value;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		exit(last_status);
	else if (i != 2)
	{
		perror("exit:too many arguments");
		return (1);
	}
	if (check_exit_value(argv[1]))
	{
		erron = 0;
		exit_value = ft_strtol(argv[1]);
		printf("exit %lu\n", exit_value);
		if(erron==0)
			// exit(exit_value);
	}
	perror("exit: numeric argument required");
	eixt(255);
}


int main(int argc,char **argv)
{
	if(bultin_exit(argv)==1);
		return 0;
	return 0;
}
