#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// cc main.c -lreadline

void    echo_cmd(char *str)
{
        printf("%s", str + 8);
}

void    cd_cmd(char *path)
{
    char s[100];
    printf("%s\n", getcwd(s, 100));
    if(chdir(path) == -1)
        printf("cd fail\n");
    printf("%s\n", getcwd(s, 100));
} 

void    pwd_cmd()
{
    char s[100];
    printf("%s\n", getcwd(s, 100));
}

void    handle_sigint(int sig)
{
    // printf("here ctrl c\n");
    // add_history("");
    // return;
}

int main() {
    char *input;

    while (1) {
        signal(SIGINT, handle_sigint);
        input = readline("Minishell~$ ");

        // If input is NULL, we've encountered an EOF (Ctrl+D)
        if (input == NULL) {
            printf("\nExiting shell.\n");
            break;
        }

        // If the input is not empty, add it to history
        if (*input) {
            add_history(input);
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // echo_cm(input);
        // cd_cm("..");
        pwd_cmd();

        // Check for exit command

        // Free allocated memory for the input
        free(input);
    }

    return 0;
}