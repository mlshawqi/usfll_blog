#include "minishell.h"


int     ft_names(char *line, char *arg)
{
    int arg_len;
    int line_len;

    arg_len = ft_strlen(arg);
    line_len = ft_strlen(line);
    if(arg_len > line_len)
        return (1);
    if((line_len > arg_len && line[arg_len] == '=') || arg_len == line_len)
        return (0);
    return (1);
}

void    update_pwd(t_env **env, char *path, char hint)
{
    t_env   *lst;

    lst = *env;
    while(lst)
    {
        if(hint == 'P' && (ft_strlen(lst->line) >= ft_strlen("PWD")) 
            && (ft_strncmp(lst->line, "PWD", 3) == 0) 
            && (lst->line[3] == '=' || lst->line[3] == '\0'))
            {
                free(lst->line);
                lst->line = ft_strjoin("PWD=", path);
                break;
            }
        else if(hint == 'O' && (ft_strlen(lst->line) >= ft_strlen("OLDPWD")) 
            && (ft_strncmp(lst->line, "OLDPWD", 6) == 0) 
            && (lst->line[6] == '=' || lst->line[6] == '\0'))
            {
                free(lst->line);
                lst->line = ft_strjoin("OLDPWD=", path);
                break;
            }
        lst = lst->next;
    }
}

int     ft_isoption(char *str)
{
    int i;

    i = 1;
    while(str[i] != '\0')
    {
        if(str[0] == '-' && str[i] == 'n')
            i++;
        else
            return (1);
    }
    return (0);
}