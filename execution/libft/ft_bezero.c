#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*t;
	size_t	i;

	t = (char *)s;
	i = 0;
	while (i < n)
	{
		t[i] = 0;
		i++;
	}
}