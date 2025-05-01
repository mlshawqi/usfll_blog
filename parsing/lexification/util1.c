#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	j;

	j = 0;
	while (s[j] != '\0')
		j++;
	return (j);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*mem;
	size_t	len;

	len = ft_strlen(s);
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (0);
	i = 0;
	while (i < len)
	{
		mem[i] = s[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		slen;
	char	*mem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	slen = ft_strlen(s1) + ft_strlen(s2);
	mem = (char *)malloc(sizeof(char) * (slen + 1));
	if (!mem)
	{
		return (0);
	}
	while (s1[i] != '\0')
	{
		mem[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		mem[i++] = s2[j++];
	mem[i] = '\0';
	return (mem);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	free_str(void *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}
