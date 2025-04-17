#include "libft.h"

int	ft_atoi(char *str, int *error)
{
	long	result;
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
		if (!check_overflow(result, str[i] - '0', sign, error))
			return (0);
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	check_overflow(long result, int digit, int sign, int *error)
{
	if (sign == 1 && result > (INT_MAX - digit) / 10)
	{
		*error = 1;
		return (0);
	}
	if ((sign == -1) && (-result < (INT_MIN + digit) / 10))
	{
		*error = 1;
		return (0);
	}
	return (1);
}
