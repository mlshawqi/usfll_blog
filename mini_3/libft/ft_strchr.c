/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:13:35 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:55:06 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*r;

	r = (char *)s;
	i = 0;
	while (r[i] != '\0')
	{
		if (r[i] == (char)c)
			return (r + i);
		i++;
	}
	if ((char)c == '\0')
		return (r + i);
	return (NULL);
}
/*
int main()
{
	char *str= NULL;
	int c = 'y';
	printf("%s",strchr(str, c));
	return (0);
}
*/
