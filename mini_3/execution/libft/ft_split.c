#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_strndup(char *s, int n)
{
	char	*str;
	int		i;

	str = malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[n] = '\0';
	return (str);
}

static void	ft_free(char **str, int k)
{
	while (k >= 0)
	{
		free(str[k]);
		k--;
	}
	free(str);
	return ;
}

static char	**ft_tosplit(char *s, char **str, char c, int len)
{
	int	k;
	int	tlen;

	k = 0;
	while (*s)
	{
		tlen = 0;
		while (*s == c)
			s++;
		while (s[tlen] != c && s[tlen] != '\0')
			tlen++;
		if (tlen > 0 && k < len && *s)
		{
			str[k] = ft_strndup(s, tlen);
			if (!str[k])
			{
				ft_free(str, k);
				return (NULL);
			}
			s += tlen;
			k++;
		}
	}
	str[k] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	len = ft_count(s, c) + 1;
	arr = malloc(len * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_tosplit(str, arr, c, len);
	return (arr);
}
