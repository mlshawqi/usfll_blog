#include "../minishell.h"

static int  invalid_numeric_input(char *str)
{
        int i;

        i = 0;
        while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
		    i++;
	    if ((str[i] == '-' || str[i] == '+') && (ft_isdigit(str[i + 1]) == 1)) 
		    i++;
        while(str[i])
        {
            if(ft_isdigit(str[i]) == 1)
                i++;
            else
                break;
        }
        if(str[i] == '\0' || str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
        {
            while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
                i++;
        }
        if(str[i] != '\0')
            return (1);
        return (0);
}

static int      is_longlong(char *str)
{
        int i;
        int len;
        int sign;

        i = 0;
        len = 0;
        sign = 0;
        while(str[i])
        {
            if(str[i] == '-' || str[i] == '+')
                sign++;
            if(ft_isdigit(str[i]) == 1)
                len++;
            i++;
        }
        if(len > 19)
            return (-1);
        return (0);
}

int    exit_cmd(t_data *data, char **arg)
{
        if (!arg || !arg[0])
        {
            write(1, "exit\n", 5);
            g_last_exit_code = 0;
            cleanup_shell_data(data, true);
        }
        if (arg[1])
        {
            print_cmd_error("exit\nminishell", "exit: too many arguments", NULL);
            return (1);
        }
        if ((invalid_numeric_input(arg[0]) == 1) || (is_longlong(arg[0]) == -1))
        {
            print_cmd_error("exit\nminishell: exit", "numeric argument required", arg[0]);
            g_last_exit_code = 2;
            cleanup_shell_data(data, true);
        }
        write(1, "exit\n", 5);
        g_last_exit_code = ft_atoii(arg[0]);
        cleanup_shell_data(data, true);
        return (0);
}
