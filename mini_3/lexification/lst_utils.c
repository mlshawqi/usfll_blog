#include "../minishell.h"

void	delete_token(t_separation *token, void (*del)(void *))
{
	if (!token || !del)
		return ;
	if (token->str)
	{
		(*del)(token->str);
		token->str = NULL;
	}
	if (token->str_copy)
	{
		(*del)(token->str_copy);
		token->str_copy = NULL;
	}
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free_str(token);
}

void	clear_token_list(t_separation **list, void (*del)(void *))
{
	t_separation	*current;
	t_separation	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		delete_token(current, del);
		current = next;
	}
	*list = NULL;
}
