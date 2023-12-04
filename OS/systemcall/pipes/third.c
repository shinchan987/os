
// using pipe and dup ,write a program where child process will excure ls -l
//  and the output will act as input for parent process which will excute sort on it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/types.h>



int main() {
    int pipefd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Close the write end of the pipe
        close(pipefd[1]);

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Wait for the child process to finish
        wait(NULL);

        // Execute the "sort" command
        execlp("sort", "sort", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
