/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgarb <zelgarb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:41:14 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 13:26:42 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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

/*int main()
{
	char str1[] = "qwertyuio";
	printf("%s", ft_strdup(str1));
	return (0);
}
*/
