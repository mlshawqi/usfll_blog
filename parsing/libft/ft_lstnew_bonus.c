/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <zelgharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:28:15 by zelgharb          #+#    #+#             */
/*   Updated: 2025/04/28 16:53:12 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*tab;

// 	tab = (t_list *)malloc(sizeof(t_list) * 1);
// 	if (!tab)
// 		return (NULL);
// 	tab->content = content;
// 	tab->next = NULL;
// 	return (tab);
// }
// int main()
// {
// 	t_list *list = NULL;
// 	t_list *node1 = ft_lstnew("ok");
// 	t_list *node2 = ft_lstnew("ok");
// 	t_list *node3 = ft_lstnew("ok");
// 	list = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	t_list *current = list;
// 	while(current)
// 	{
// 		printf("%s->", (char *)current->content);
// 		current = current->next;
// 	}
// 	printf("NULL\n");
//     return (0);
// }
