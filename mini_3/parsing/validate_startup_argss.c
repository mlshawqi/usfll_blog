#include "../minishell.h"

bool	validate_startup_args(t_data *data, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (usage_message(false));
	if (ac == 3)
	{
		data->interactive = false;
		if (!av[1] || ft_strcmp(av[1], "-c") != 0)
			return (usage_message(false));
		if (!av[2] || av[2][0] == '\0')
			return (usage_message(false));
	}
	else
		data->interactive = true;
	return (true);
}
