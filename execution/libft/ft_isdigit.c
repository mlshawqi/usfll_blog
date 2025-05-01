#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	ft_isempty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_sign(char *str, int i)
{
	if (ft_isspace(str[i - 1]) && (str[i] == '-'
			|| str[i] == '+') && ft_isdigit(str[i + 1]))
		return (1);
	return (0);
}
