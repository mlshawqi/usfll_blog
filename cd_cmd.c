#include "minishell.h"

void    cd_cmd(char *path)
{
    if(chdir(path) == -1)
        printf("cd fail\n");
}