/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:57:39 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:34:37 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *p, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)p;
	while (i < len)
	{
		ptr[i] = (unsigned char )c;
		i++;
	}
	return (p);
}
/*
int main()
{
	char str[30] = "wertyuio";
	ft_memset(str, '*',30);
	printf("%s", str);
	return (0);
}
int main()
{
    char str[5]; 

    
    ft_memset(str, '1', 1); 
    ft_memset(str + 1, '3', 1);
    ft_memset(str + 2, '3', 1);
    ft_memset(str + 3, '7', 1); 
    str[4] = '\0'; 

    printf("%s\n", str); 
    return (0);
}
*/
