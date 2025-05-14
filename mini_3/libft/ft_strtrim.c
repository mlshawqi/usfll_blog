/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgarb <zelgarb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:14 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 21:22:42 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	test(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	end;
	size_t	len;
	char	*mem;

	if (!s1 || !set)
		return (0);
	debut = 0;
	while (s1[debut] && test(s1[debut], set))
		debut++;
	end = ft_strlen(s1);
	while (end > debut && test(s1[end - 1], set))
		end--;
	len = end - debut;
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (0);
	ft_strlcpy(mem, (char *)(s1 + debut), len + 1);
	return (mem);
}
// int main()
// {
// 	char str[] = "     oouuuuuu    uoooo       ";
// 	char s2[] = " ";
// 	printf("%s", ft_strtrim(str,s2));
// 	return (0);
// }
