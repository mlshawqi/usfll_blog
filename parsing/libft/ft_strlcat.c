/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:59:48 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:53:20 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	if (!dst && size == 0)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	j = dstlen;
	if (size <= j || size == 0)
		return (size + srclen);
	i = 0;
	while (j < size - 1 && i < srclen)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srclen + dstlen);
}
/*
int main()
{
	char src[] = "qqqqqq";
	char dst[20] = "iiiiii";
	printf("%ld",strlcat(NULL,src,20));
	return (0);
}
*/
