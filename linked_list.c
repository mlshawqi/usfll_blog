#include "minishell.h"

void	link_node(t_env **head, char *line)
{
	t_env	*new_node;
	t_env	*current;
        int     len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		return ;
	}
	len = strlen(line);
        new_node->line = malloc(sizeof(char) * len + 1);
        if(!new_node->line)
                return;
        strcpy(new_node->line, line);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
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

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}