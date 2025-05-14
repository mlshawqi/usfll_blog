/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgarb <zelgarb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:48:55 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 17:30:13 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nmemb != 0 && (SIZE_MAX / nmemb) < size)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
/*
int main()
{
	char *array;
	array = (char *)ft_calloc(7,sizeof(array));
	for(int i = 0;i < 7;i++)
	{
		printf("%d",array[i]);
	}
	
	return (0);
}
int main()
{
	char str[] = "wertyui";
	char *array;
	array = (char *)ft_calloc(7,sizeof(str));
	for(int i = 0;i < sizeof(str);i++)
	{
		array[i] = str[i];
	}
	printf("%s",array);
	return (0);
}
int main()
{
	int *array;
	array = (int *)ft_calloc(8, sizeof(int));
	for(int i = 0;i < 8;i++)
	{
		printf("%d",array[i]);
	}
	return (0);
}
*/
