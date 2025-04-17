#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

	if (!lst)
		return (0);
	len = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}