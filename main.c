#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// cc main.c -lreadline

// void    echo_cmd(char *str)
// {
//         printf("%s", str + 8);
// }

// void    cd_cmd(char *path)
// {
//     char s[100];
//     printf("%s\n", getcwd(s, 100));
//     if(chdir(path) == -1)
//         printf("cd fail\n");
//     printf("%s\n", getcwd(s, 100));
// } 

// void    pwd_cmd()
// {
//     char s[100];
//     printf("%s\n", getcwd(s, 100));
// }

void handle_sigint(int sig) {
    rl_redisplay();           // Refresh the display
    printf("\nMinishell~$ ");   // Print the prompt after Ctrl+C
}

int main(int argc, char **argv, char **env) {
    char *input;

    signal(SIGINT, handle_sigint);
    while (1) {
        input = readline("Minishell~$ ");
        if (input == NULL || (strcmp(input, "exit") == 0))
        {
            printf("exit\n");
            free(input);
            break;
        }
        if (*input) {
            add_history(input);
        }

        // echo_cm(input);
        // cd_cm("..");
        printf("input = %s\n", input);

        free(input);
    }
    rl_clear_history();
    return 0;
}