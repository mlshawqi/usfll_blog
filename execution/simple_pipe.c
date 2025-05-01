#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
        int fd[2];
        // fd[0] === read
        // fd[1] === write
        if(pipe(fd) == -1)
        {
                printf("pipe fail\n");
                return (1);
        }
        int id = fork();

        // The child process
        if (id == 0) {
                close(fd[0]);
                int x = 30;
                write(fd[1], &x, sizeof(int));
                close(fd[1]);
        } else {
                close(fd[1]);
                int y;
                read(fd[0], &y, sizeof(int));
                printf("from parent %d\n", y);
                close(fd[0]);
        }
 
    return 0;
}