#include "../minishell.h"

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		// if (data->cmd && data->cmd->io_fds)
		// 	close_files_descriptors(data->cmd, true);
		cleanup_shell_data(data, true);
	}
	exit(exno);
}
