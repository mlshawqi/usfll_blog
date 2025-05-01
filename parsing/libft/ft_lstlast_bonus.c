/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:46:05 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:19:16 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
// int main()
// {
// 	t_list *list = NULL;
// 	t_list *node1 = ft_lstnew("ok");
// 	t_list *node2 = ft_lstnew("ok");
// 	t_list *node3 = ft_lstnew("ok");
// 	list = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	t_list *last_noeud = ft_lstlast(list);
// 	printf("%s",(char *)last_noeud->content);
// 	return (0);
// }
