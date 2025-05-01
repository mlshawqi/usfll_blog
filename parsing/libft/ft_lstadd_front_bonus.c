/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:59:26 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 18:50:20 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
// int main()
// {
// 	t_list *list = NULL;
// 	t_list *new_node1 = ft_lstnew("la vie");
// 	t_list *new_node2 = ft_lstnew("est");
// 	t_list *new_node3 = ft_lstnew("belle");
// 	ft_lstadd_front(&list, new_node3);
// 	ft_lstadd_front(&list, new_node2);
// 	ft_lstadd_front(&list, new_node1);
// 	t_list	*current = list;
//     while (current)
//     {
//         printf("%s -> ", (char *)current->content);
 // Afficher le contenu de chaque élément
//         current = current->next;// Passer au suivant
//     }
//     printf("NULL\n");

//     return (0);
// }*/
