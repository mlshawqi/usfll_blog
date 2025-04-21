#include "minishell.h"


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

t_env	*ft_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_env *lst)
{
	int		len;
	t_env	*tmp;

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