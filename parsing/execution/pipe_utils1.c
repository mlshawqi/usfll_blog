#include "../minishell.h"

void    free_tab(int **arr, int i)
{
        if(!arr)
                return ;
        while (i >= 0)
        {
                if(arr[i])
                {
                        free(arr[i]);
                        arr[i] = NULL;
                }
                i--;
        }
        free(arr);
        arr = NULL;
}

int     **allocate_pipes(int count)
{
        int     **arr;
        int     i;

        arr = ft_calloc(count, sizeof(int *));
        if(!arr)
                return (NULL);
        i = 0;
        while(i < count)
        {
                arr[i] = ft_calloc(2, sizeof(int));
                if(!arr[i])
                {
                        free_tab(arr, i - 1);
                        return (NULL);
                }
                if(pipe(arr[i]) == -1)
                {
                        free_tab(arr, i);
                        perror("pipe failed");
                        return (NULL);
                }
                i++;
        }
        return (arr);
}

void    close_pipes(int **pipes,int count)
{
        int     i;

        i = 0;
        while (i < count)
        {
                close(pipes[i][0]);
                close(pipes[i][1]);
                i++;
        }
}