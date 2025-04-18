#include "minishell.h"

void	link_node(t_env **head, char *line)
{
	t_env	*new_node;
	t_env	*current;

	new_node = ft_lstnew(line);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
	}
}

t_env	*ft_lstnew(char *content)
{
	t_env	*new_node;
	int	len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	len = strlen(content);
        new_node->line = malloc(sizeof(char) * len + 1);
        if(!new_node->line)
                return (NULL);
        ft_strlcpy(new_node->line, content, len + 1);
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

// t_env	*ft_lstlast(t_env *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstadd_front(t_env **lst, t_env *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }