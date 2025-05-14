/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:23:35 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 17:29:40 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	taille(long long int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*fill(char *str, long long int n, int len)
{
	int	debut;

	str[len] = '\0';
	len = len -1;
	if (n < 0)
	{
		n = -n;
		debut = 1;
		str[0] = '-';
	}
	else
		debut = 0;
	while (len >= debut)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	long long int	longueur;

	longueur = (long long int)n;
	len = taille(longueur);
	if (longueur < 0)
		len = len + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (fill(str, longueur, len));
}
/*
int	main()
{
	printf("%s",ft_itoa(1234567890));
}
*/
