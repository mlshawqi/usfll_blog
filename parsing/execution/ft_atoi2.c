#include "../minishell.h"

static int	check_overflow(int sign, unsigned long long nbr)
{
	if (sign < 0)
	{
		if(nbr > MIN_LONG)
		{
			printf("minishell: exit: numeric argument required\n");
			return (-1);
		}
	}
	else
	{
		if(nbr > MAX_LONG)
		{
			printf("minishell: exit: numeric argument required\n");
			return (-1);
		}
	}
	return (0);
}

long long	ft_atoii(const char *str)
{
	unsigned long long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		if (check_overflow(sign, result) == -1)
			return (2);
		i++;
	}
	return (result * sign);
}