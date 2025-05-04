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

int    ft_execve(t_data *data)
{
        char    **env_arr;
        char    *path;
        int     pid;
        int     status;

        env_arr = env_to_array(data->env);
        path = find_program_path(data->env, data->cmd->command);
        if(path == NULL)
        {
                printf("%s: command not found\n", data->cmd->command);
                return (127);
        }
        pid = fork();
        if(pid == 0)
        {
                if(execve(path, data->cmd->args, env_arr) == -1) perror("execve");
                return (127);
        }
        else
        {
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)) return WEXITSTATUS(status);
        }
        free(path);
        return (0);
}
