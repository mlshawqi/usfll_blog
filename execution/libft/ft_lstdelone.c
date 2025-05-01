/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-10 10:12:39 by machaouk          #+#    #+#             */
/*   Updated: 2025/02/10 11:41:16 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst == NULL)
		return ;
	del(lst->arr);
	free(lst);
}

void	del(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	while (t[i] != NULL)
	{
		free(t[i]);
		i++;
	}
	free(t);
}
