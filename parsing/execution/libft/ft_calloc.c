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

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*str;
// 	size_t	i;

// 	i = 0;
// 	if (size != 0 && count > (SIZE_MAX / size))
// 		return (NULL);
// 	str = malloc(count * size);
// 	if (!str)
// 		return (NULL);
// 	ft_bzero(str, count * size);
// 	return ((void *)str);
// }