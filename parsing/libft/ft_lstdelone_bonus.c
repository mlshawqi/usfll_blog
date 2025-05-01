/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:35:58 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:16:10 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
// int main()
// {
// 	void del_function(void *content)
// {
//     printf("Suppression : %s\n", (char *)content);
// }
// 	t_list *list  = NULL;
// 	t_list *node1 = ft_lstnew("la vie");
// 	t_list *node2 = ft_lstnew("est");
// 	t_list *node3 = ft_lstnew("belle");
// 	list = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	printf("Suppression du premier nœud...\n");
//     t_list *next_node = list->next;  // Sauvegarder le prochain nœud
//     ft_lstdelone(list, del_function); // Supprimer le premier nœud
//     list = next_node;  
// Mettre à jour la liste pour pointer sur le prochain nœud
//     // Afficher la liste après suppression
//     printf("Liste après suppression :\n");
// 	t_list *current = list;
//     while (current)
//     {
//         printf("%s -> ", (char *)current->content);
//         current = current->next;
//     }
// 	printf("NULL\n");
//     return (0);
// }*/
