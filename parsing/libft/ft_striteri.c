/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:11:44 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 21:23:26 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int		i;

	i = 0;
	while (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int main()
{
	void f(unsigned int i, char *c)
	{
		if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
			*c = (*c - 32);
	}
	char str[] = "sdfghjk";
	ft_striteri(str,f);
	printf("%s", str);
}
*/
