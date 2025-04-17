#include "minishell.h"

void    pwd_cmd()
{
        char *pwd;

        pwd = getcwd(NULL, 0);
        printf("pwd: %s\n", pwd);
}


void    echo_cmd(char *str)
{
        printf("%s", str + 8);
}

void    cd_cmd(char *path)
{
    if(chdir(path) == -1)
        printf("cd fail\n");
}

void    env_cmd(t_env *lst)
{
        while(lst != NULL)
        {
            printf("%s\n", lst->line);
            lst = lst->next;
        }
}