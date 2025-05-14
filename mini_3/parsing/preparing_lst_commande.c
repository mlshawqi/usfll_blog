#include "../minishell.h"

void	init_command(t_cmd **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->io_fds = NULL;
	(*cmd)->pipex = NULL;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_cmd	*create_command(bool pipe_output)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	// ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->pipe_output = pipe_output;
	init_command(&cmd);
	return (cmd);
}

void	add_command_to_list(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*start;

	start = *list;
	if (start == NULL)
	{
		*list = new_cmd;
		return ;
	}
	if (list && *list && new_cmd)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_cmd;
		new_cmd->prev = start;
	}
}

t_cmd *get_last_command(t_cmd *cmd)
{
	while (cmd && cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
