/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:43:50 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 19:10:44 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = node;
	}
	*lst = NULL;
}
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
// 	t_list *current = list;
//     while (current)
//     {
//         printf("%s -> ", (char *)current->content);
//         current = current->next;
//     }
// 	printf("NULL\n");
// 	ft_lstclear(&list, del_function);
// 	  if (!list)
//         printf("\nLa liste est maintenant vide.\n");

//     return (0);
// }
