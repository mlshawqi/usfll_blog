/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:06:36 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:56:25 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		found;

	i = 0;
	found = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			found = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	if (found != -1)
		return ((char *)(s + found));
	return (NULL);
}
/*
int	main()
{
	char str[] = "eeee";
	int c = 'e';
	printf("%s",strrchr(NULL, c));
	return (0);
}
*/
