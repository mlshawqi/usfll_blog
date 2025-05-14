#include "../minishell.h"

int g_last_exit_code = 0;

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		set_signals();
		data->user_input = readline("minishell~$ ");
		// configure_noninteractive_signals();
		if (!data->user_input)
		{
			printf("exit\n");
			break ;
		}
		process_user_input(data);
		if(data->cmd)
			execution(data);
		cleanup_shell_data(data, false);
	}
}

void	minishell_noninteractive(t_data *data, char *arg)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	if (user_inputs[i])
	{
		data->user_input = ft_strdup(user_inputs[i]);
		process_user_input(data);
		if(data->cmd)
			execution(data);
		cleanup_shell_data(data, false);
	}
	free_string_array(user_inputs);
}

int main(int ac, char **av, char **env)
{
    t_data data;

//     ft_memset(&data, 0, sizeof(t_data));
    if (!ft_initialise_data(&data, env)) {
        print_command_error("Fatal", NULL, "Could not initialize environment", 1);
        exit_shell(NULL, EXIT_FAILURE);
    }
    if (!validate_startup_args(&data, ac, av)) {
        exit_shell(&data, EXIT_FAILURE);
    }
    if (data.interactive) {
        minishell_interactive(&data);
    }
    else {
        minishell_noninteractive(&data, av[2]);
    }
    exit_shell(&data, g_last_exit_code);
    exit (g_last_exit_code);
}
