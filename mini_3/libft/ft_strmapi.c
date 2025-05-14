/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:40:15 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:16:06 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t				len;
	unsigned int		i;
	char				*mem;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (0);
	while (i < len)
	{
		mem[i] = f(i, s[i]);
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
/*
char f(unsigned int i, char c)
{
	if(i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
int main()
{

	char str[] ="qwerty";
	printf("%s", ft_strmapi(str,f));
}
*/
