/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:34:02 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:56:37 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
// #include <fcntl.h>  
// int main()
// {
// 	int fd = open("fd2.txt", O_WRONLY | O_CREAT | O_TRUNC);
// 	ft_putendl_fd("wertyui", fd);
// 	return (0);
// }
