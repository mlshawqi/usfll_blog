/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgharb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:03:40 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/13 18:14:30 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// int main()
// {
// 	void	print_content(void *content)
// {
//     printf("%s -> ", (char *)content);
// }

// 	t_list *list  = NULL;
// 	t_list *node1 = ft_lstnew("la vie");
// 	t_list *node2 = ft_lstnew("est");
// 	t_list *node3 = ft_lstnew("belle");
// 	list = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	ft_lstiter(list, print_content);
// 	printf("NULL\n");
// }
