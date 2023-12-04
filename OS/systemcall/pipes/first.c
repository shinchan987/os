// read from parent and write to child using pipe


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/types.h>

#define BUFFER_SIZE 50

int main() {
    int pipefd[2]; // File descriptors for the pipe
    int child_pid;
    char buffer[BUFFER_SIZE];

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
        close(pipefd[0]); // Close the read end of the pipe in the child

        // Data to be sent from child to parent
        char message[] = "Hello from the child process!";

        // Write the message to the pipe
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]); // Close the write end of the pipe in the child

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe in the parent

        // Read the message from the pipe
        read(pipefd[0], buffer, sizeof(buffer));

        // Print the received message
        printf("Message from child: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe in the parent

        wait(NULL); // Wait for the child to finish

        exit(EXIT_SUCCESS);
    }

    return 0;
}
