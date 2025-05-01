/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:18:53 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:58:57 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
// #include <fcntl.h>  
// int main()
// {
// 	int fd = open("fd3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	ft_putstr_fd("wertyu", fd);
// 	return (0);
// }
