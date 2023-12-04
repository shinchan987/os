// Write a program that creates a child process. Parent process writes data to pipe and child process reads
// the data from pipe and prints it on the screen.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<fcntl.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {  // Child process
        close(pipe_fd[1]);  // Close the write end of the pipe

        char buffer[100];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        buffer[bytes_read] = '\0';

        printf("Child Process Received: %s\n", buffer);
        
        close(pipe_fd[0]);  // Close the read end of the pipe
    } else {  // Parent process
        close(pipe_fd[0]);  // Close the read end of the pipe

        const char* message = "Hello from the parent process!";
        write(pipe_fd[1], message, strlen(message));

        close(pipe_fd[1]);  // Close the write end of the pipe
    }

    return 0;
}
