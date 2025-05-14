#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (d == s || n == 0)
		return (dest);
	if (s < d && s + n > d)
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
