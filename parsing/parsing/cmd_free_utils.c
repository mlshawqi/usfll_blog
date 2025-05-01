#include "../minishell.h"


void	free_command(t_cmd *cmd, void (*del)(void *))
{
	if (!cmd)
		return ;
	if (cmd->command)
		(*del)(cmd->command);
	if (cmd->args)
		free_string_array(cmd->args);
	// if (cmd->pipe_fd)
	// 	(*del)(cmd->pipe_fd);
	if (cmd->io_fds)
		free_in_out(cmd->io_fds);
	(*del)(cmd);
}


void	free_command_list(t_cmd **cmd_list, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*cmd_list)
	{
		temp = (*cmd_list)->next;
		free_command(*cmd_list, del);
		*cmd_list = temp;
	}
}
