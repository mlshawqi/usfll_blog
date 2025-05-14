/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:04:26 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:50:24 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t						i;
	const unsigned char			*s1;
	const unsigned char			*s2;

	s1 = (const unsigned char *)ptr1;
	s2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	const unsigned char s1[] = "wert";
	const unsigned char s2[] = "weuo";
	size_t i = 1;
	printf("%d",ft_memcmp(s1, s2, i));
	return (0);
}
*/
