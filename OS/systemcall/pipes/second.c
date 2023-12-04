// read from parent and write to child using pipem string is taken from user

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
    char inputString[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Prompt the user for input
 
    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
           printf("Enter a string: ");
           fgets(inputString, sizeof(inputString), stdin);

        close(pipefd[0]); // Close the read end of the pipe in the child

        // Write the user input to the pipe
        write(pipefd[1], inputString, strlen(inputString) + 1);

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
