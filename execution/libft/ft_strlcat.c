#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	t;

	if (size == 0)
		return (ft_strlen(src));
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (dlen >= size)
		return (size + slen);
	i = dlen;
	t = 0;
	while (i < (size - 1) && t < slen)
	{
		dest[i] = src[t];
		i++;
		t++;
	}
	dest[i] = '\0';
	return (dlen + slen);
}