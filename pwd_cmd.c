#include "minishell.h"

void    pwd_cmd()
{
        char *pwd;

        pwd = getcwd(NULL, 0);
        printf("pwd: %s\n", pwd);
}