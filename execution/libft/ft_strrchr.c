#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	found;

	i = 0;
	found = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			found = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	if (found != -1)
		return ((char *)(s + found));
	return (NULL);
}