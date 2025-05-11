#include "../minishell.h"

int print_command_error(char *command, char *detail, char *error_message, int error_code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (command)
	{
		write(STDERR_FILENO, command, strlen(command));
		write(STDERR_FILENO, ": ", 2);
	}
	if (detail)
	{
		write(STDERR_FILENO, detail, strlen(detail));
		write(STDERR_FILENO, ": ", 2);
	}
	if (error_message)
		write(STDERR_FILENO, error_message, strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
	return error_code;
}

void display_error_message(char *error_text, const char *info, int use_quotes)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, error_text, strlen(error_text));

	if (use_quotes)
		write(STDERR_FILENO, " `", 2);
	else
		write(STDERR_FILENO, ": ", 2);

	if (info)
		write(STDERR_FILENO, info, strlen(info));

	if (use_quotes)
		write(STDERR_FILENO, "'", 1);

	write(STDERR_FILENO, "\n", 1);
}

bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
