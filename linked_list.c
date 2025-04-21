#include "minishell.h"

void	link_node(t_env **head, char *line, char hint)
{
	t_env	*new_node;
	t_env	*current;

	new_node = ft_lstnew(line, hint);
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

t_env	*ft_lstnew(char *content, char hint)
{
	t_env	*new_node;
	int	len;
	char	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if(hint == 'c')
	{
		tmp = manage_line(content);
		new_node->line = ft_strjoin("declare -x ", tmp);
		free(tmp);
	}
	else
	{
		len = strlen(content) + 1;
		new_node->line = malloc(sizeof(char) * len);
		if(!new_node->line)
			return (NULL);
		ft_strlcpy(new_node->line, content, len + 1);

	}
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}
char	*manage_line(char *line)
{
	int	len;
	char	*quotes_line;

	if(ft_strchr(line, '='))
		len = ft_strlen(line) + 3;
	else
		len = ft_strlen(line) + 1;
	quotes_line = malloc(sizeof(char) * len);
        if(!quotes_line)
                return (NULL);
	put_quotes_sign(line, quotes_line);
	return (quotes_line);
}

void	put_quotes_sign(char *line, char *env)
{
	int	i;
	int	j;
	int	sign;

	i = 0;
	j = 0;
	sign = 0;
	while(line[i] != '\0')
	{
		env[j] = line[i];
		if(line[i] == '=' && sign == 0)
		{
			env[j + 1] = '"';
			j++;
			sign++;
		}
		i++;
		j++;
	}
	if(sign > 0)
	{
		env[j] = '"';
		j++;
	}
	env[j] = '\0';
}
