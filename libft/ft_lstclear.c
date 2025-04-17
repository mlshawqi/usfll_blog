/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-10 10:12:33 by machaouk          #+#    #+#             */
/*   Updated: 2025-02-10 10:12:33 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*p;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		p = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = p;
	}
	*lst = NULL;
}
