#include "libft.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tp = ft_lstlast(*lst);
		tp->next = new;
		new->previous = tp;
	}
}