#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// cc main.c -lreadline

void    echo_cm(char *str)
{
        printf("%s", str + 8);
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
        // Here you can process the input as needed
        echo_cm(input);

        // Check for exit command

        // Free allocated memory for the input
        free(input);
    }

    return 0;
}