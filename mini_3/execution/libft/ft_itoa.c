#include "libft.h"

static int	ft_lent(long t)
{
	int	len;

	len = 0;
	if (t == 0)
		return (1);
	if (t < 0)
	{
		t *= -1;
		len++;
	}
	while (t > 0)
	{
		t = t / 10;
		len++;
	}
	return (len);
}

static void	ft_str(char *s, int len, long nb)
{
	if (nb >= 10)
	{
		ft_str(s, len - 1, nb / 10);
		s[len] = (nb % 10) + '0';
	}
	else
		s[len] = nb + 48;
}

char	*ft_itoa(int n)
{
	int		i;
	long	nbr;
	char	*str;

	nbr = n;
	i = ft_lent(nbr);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	else if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	ft_str(str, i - 1, nbr);
	return (str);
}
