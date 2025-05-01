#include "libft.h"

static int	check(char const *str, char c)
{
	int	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		slen;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	slen = ft_strlen(s1);
	while (s1[i] != '\0' && check(set, s1[i]) == 1)
		i++;
	while (slen > i && check(set, s1[slen - 1]) == 1)
		slen--;
	if (i == slen)
		return (ft_strdup(""));
	return (ft_substr(s1, i, slen - i));
}