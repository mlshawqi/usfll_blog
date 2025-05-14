/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:46:51 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 13:30:03 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	if ((slen - start) < len)
		len = slen - start;
	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s + start, len + 1);
	return (mem);
}
/*
int main()
{
	char str[] = "wwwwwwwwwwwwwwwwwww";
	unsigned int i =7;
	size_t n = 10;
	char *mem = ft_substr(str, i,n);
	printf("%s",mem);
	return (0);
}
*/
