#include "../minishell.h"

void	set_signals(void)
{
	signal(SIGINT, reset_input_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_input_prompt(int signo)
{
	g_last_exit_code = 130;
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	configure_interactive_signals(void)
{
	struct sigaction	act;

	ignore_quit_signal();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = reset_input_prompt;
	sigaction(SIGINT, &act, NULL);
}
void	ignore_quit_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

 void	handle_signal_newline(int signo)
 {
 	(void)signo;
 	rl_on_new_line();
 }

 void	configure_noninteractive_signals(void)
 {
 	struct sigaction	act;

 	ft_memset(&act, 0, sizeof(act));
 	act.sa_handler = &handle_signal_newline;
 	sigaction(SIGINT, &act, NULL);
 	sigaction(SIGQUIT, &act, NULL);
 }