#include "../minishell.h"

char    **env_to_array(t_env *env)
{
        int     i;
        char    **array;
        char    *tmp;

        i = 0;
        array = malloc(sizeof(char *) * ft_lstsize(env) + 1);
        while(env)
        {
                tmp = ft_strjoin(env->name, "=");
                array[i] = ft_strjoin(tmp, env->value);
                free(tmp);
                env = env->next;
                i++;
        }
        array[i] = NULL;
        return (array);
}

char     *find_program_path(t_env *env, char *cmd)
{
        char    **arr;
        char    *path;
        char    *tmp;
        int     i;

        while(env)
        {
                if(ft_strcmp(env->name, "PATH") == 0)
                        arr = ft_split(env->value, ':');
                env = env->next;
        }
        i = 0;
        path = NULL;
        while(arr[i])
        {
                tmp = ft_strjoin(arr[i], "/");
                path = ft_strjoin(tmp, cmd);
                free(tmp);
                if(access(path, X_OK) == 0)
                        break;
                free(path);
                path = NULL;
                i++;
        }
        return (path);
}

int    ft_execve(t_env *env, char *cmd, char **args)
{
        char    **env_arr;
        char    *path;
        int     pid;
        int     status;

        env_arr = env_to_array(env);
        path = find_program_path(env, cmd);
        if(path == NULL)
        {
                perror(NULL);
                return (-1);
        }
        pid = fork();
        if(pid == 0)
        {
                if(execve(path, args, env_arr) == -1)
                        printf("execve fail\n");
                return (-1);
        }
        else
        {
                waitpid(pid, &status, 0);
                return (0);
        }
        return (0);
}