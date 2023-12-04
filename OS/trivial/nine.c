// Write a program that creates two children, and connects the standard output of one to the standard
// input of the other, using the pipe() system call such that second child should able to print some
// random message received from first child.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <string.h>
#include<fcntl.h>
int main() {
    int pipe_fd[2];
    pid_t child1_pid, child2_pid;

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    // Create the first child process
    child1_pid = fork();

    if (child1_pid == -1) {
        perror("Fork (child1) failed");
        exit(1);
    }

    if (child1_pid == 0) {  // First child process
        close(pipe_fd[0]);  // Close the read end of the pipe

        // Redirect standard output to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe, as it is now redundant
        close(pipe_fd[1]);

        // Generate a random message
        char message[] = "Hello from Child 1!";
        write(STDOUT_FILENO, message, sizeof(message));

        exit(0);
    } else {  // Parent process
        // Create the second child process
        child2_pid = fork();

        if (child2_pid == -1) {
            perror("Fork (child2) failed");
            exit(1);
        }

        if (child2_pid == 0) {  // Second child process
            close(pipe_fd[1]);  // Close the write end of the pipe

            // Redirect standard input to the read end of the pipe
            dup2(pipe_fd[0], STDIN_FILENO);

            // Close the read end of the pipe, as it is now redundant
            close(pipe_fd[0]);

            // Read and print the message from the first child
            char buffer[100];
            int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
            buffer[bytesRead] = '\0';
            printf("Child 2 received: %s\n", buffer);

            exit(0);
        }

        // Close both ends of the pipe in the parent process
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Wait for both child processes to finish
        wait(NULL);
        wait(NULL);
    }

    return 0;
}
