#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include <readline/readline.h>
#include <readline/history.h>

// cc main.c -lreadline

void    echo_cm(char *str)
{
        printf("%s", str + 8);
}

void    cd_cm(char *path)
{
    char s[100];
    printf("%s\n", getcwd(s, 100));
    if(chdir(path) == -1)
        printf("cd fail\n");
    printf("%s\n", getcwd(s, 100));
}

void    pwd_cm()
{
    char s[100];
    printf("%s\n", getcwd(s, 100));
}

int main() {
    char *input;

    while (1) {
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
        pwd_cm();

        // Check for exit command

        // Free allocated memory for the input
        free(input);
    }

    return 0;
}