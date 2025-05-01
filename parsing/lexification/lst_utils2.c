#include "../minishell.h"

void	connect_nodes(t_separation *to_remove,
	t_separation *current, t_separation *new_nodes)
{
	while (current != to_remove)
		current = current->next;
	new_nodes->prev = current->prev;
	if (current->prev)
		current->prev->next = new_nodes;
	while (new_nodes->next)
		new_nodes = new_nodes->next;
	new_nodes->next = current->next;
	if (current->next)
		current->next->prev = new_nodes;
}

t_separation	*replace_in_list(t_separation **head,
	t_separation *to_remove, t_separation *new_nodes)
{
	t_separation	*current;

	current = *head;
	if (!head || !to_remove || !new_nodes)
		return (NULL);
	if (!current)
		*head = new_nodes;
	else if (current == to_remove)
	{
		*head = new_nodes;
		new_nodes->next = current->next;
		if (current->next)
			current->next->prev = new_nodes;
	}
	else
		connect_nodes(to_remove, current, new_nodes);
	free_str(to_remove->str);
	free_str(to_remove);
	return (new_nodes);
}
