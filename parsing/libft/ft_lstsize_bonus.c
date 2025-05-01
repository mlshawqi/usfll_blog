/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:17:15 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:44:46 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list		*node;
	int			count;

	count = 0;
	node = (t_list *)lst;
	if (!lst)
		return (count);
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}
// int main()
// {
// 	t_list *list;
// 	t_list *node1 = ft_lstnew("ok");
// 	t_list *node2 = ft_lstnew("ok1");
// 	t_list *node3 = ft_lstnew("ok2");
// 	list = node1;
// 	node1->next = node2;
// 	node2->next = node3;
//     printf("La taille de la liste est : %d\n", ft_lstsize(list));
// 	return (0);
// }
