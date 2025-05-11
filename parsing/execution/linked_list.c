#include "../minishell.h"

void    copy_env(char **env, t_env **list)
{
    int i;

    i = 0;
    while(env[i])
    {
        link_node(list, ft_lstnew(env[i]));
        i++;
    }
}

void	link_node(t_env **head, t_env *new_node)
{
	t_env	*current;

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

t_env	*ft_lstnew(char *line)
{
	t_env	*new_node;
	int	name_len;
	int	value_len;

	name_len = ft_strchr(line, '=') - line;
	value_len = ft_strlen(ft_strchr(line, '=') + 1);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (malloc_error("t_env"), NULL);
	new_node->name = malloc(sizeof(char) * name_len + 1);
	if(!new_node->name)
		return (malloc_error("t_env"), NULL);
	new_node->value = malloc(sizeof(char) * value_len + 1);
	if(!new_node->value)
		return (malloc_error("t_env"), NULL);
	ft_strlcpy(new_node->name, line, name_len + 1);
	ft_strlcpy(new_node->value, ft_strchr(line, '=') + 1, value_len + 1);
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

t_env    *new_node(char *arg)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if(!new)
        return (malloc_error("t_env"), NULL);
    ft_strlcpy(new->name, arg, (ft_strchr(arg, '+') - arg));
    new->value = ft_strdup(ft_strchr(arg, '=') + 1);
    new->next = NULL;
    new->previous = NULL;
    return (new);
}

