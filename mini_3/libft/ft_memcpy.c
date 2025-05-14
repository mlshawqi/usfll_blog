/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:45:04 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:43:10 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int main()
{
char dst[7];
char src[] = "xcvbn";
ft_memcpy(NULL, "rtyuio", 0);
printf("%s",dst);
return (0);
}
*/
