/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelgarb <zelgarb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:17:43 by zelgharb          #+#    #+#             */
/*   Updated: 2024/11/11 21:28:02 by zelgharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*content;
	t_list	*save;

	if (!lst || !f || !del)
		return (0);
	save = NULL;
	while (lst)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new)
		{
			free(content);
			ft_lstclear(&save, del);
			return (0);
		}
		ft_lstadd_back(&save, new);
		lst = lst->next;
	}
	return (save);
}
