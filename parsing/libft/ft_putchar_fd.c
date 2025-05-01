/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:01:42 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/12 22:06:47 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <fcntl.h>  
int main()
{
 	int fd = open("fd1.txt", O_WRONLY | O_CREAT | O_TRUNC);
 	ft_putchar_fd('A', fd);
	printf("%d", fd);
	return (0);
 }
*/
