/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgarb <zelgarb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:50:59 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 13:27:20 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
/*
int main()
{
	char const s1[] = "hello ";
	char const s2[] = "zineb";
	printf("%s", ft_strjoin(s1,s2));
	return (0);
}
*/
