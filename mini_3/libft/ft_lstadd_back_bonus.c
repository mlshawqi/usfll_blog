/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:20:30 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/10 22:27:17 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = ft_lstlast(*(lst));
			node->next = new;
		}
	}
}
/*
// int	main(void)
// {
//     t_list	*list = NULL;
//     t_list	*new_node1 = ft_lstnew("la vie");
// 	t_list	*new_node2 = ft_lstnew("est");
// 	t_list	*new_node3 = ft_lstnew("belle");
// 	ft_lstadd_back(&list, new_node1);
// 	ft_lstadd_back(&list, new_node2);
// 	ft_lstadd_back(&list, new_node3);
// 	t_list	*current = list;
//     while (current)
//     {
//         printf("%s -> ", (char *)current->content); 
// Afficher le contenu de chaque élément
//         current = current->next;                   // Passer au suivant
//     }
//     printf("NULL\n");

//     return (0);
// }
*/
