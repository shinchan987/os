#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 50






int main() {
    int pipe1[2]; // Pipe for communication 1
    int pipe2[2]; // Pipe for communication 2
    pid_t child_pid;
    char message1[] = "Hello from child!"; // Message from child to parent
    char message2[BUFFER_SIZE]; // Message from parent to child
    if (pipe(pipe1) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create pipe 2
    if (pipe(pipe2) == -1) {
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

        close(pipe1[0]); // Close the read end of pipe 1 in the child
        close(pipe2[1]); // Close the write end of pipe 2 in the child

        // Write message1 to the parent through pipe 1
        write(pipe1[1], message1, strlen(message1) + 1);

        // Read message2 from the parent through pipe 2
        read(pipe2[0], message2, sizeof(message2));

        printf("Child received: %s\n", message2);

        close(pipe1[1]); // Close the write end of pipe 1 in the child
        close(pipe2[0]); // Close the read end of pipe 2 in the child

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        close(pipe1[1]); // Close the write end of pipe 1 in the parent
        close(pipe2[0]); // Close the read end of pipe 2 in the parent

        // Read message1 from the child through pipe 1
        read(pipe1[0], message2, sizeof(message2));
        printf("Parent received: %s\n", message2);

        // Write message2 to the child through pipe 2
        write(pipe2[1], "Hello from parent!", strlen("Hello from parent!") + 1);

        close(pipe1[0]); // Close the read end of pipe 1 in the parent
        close(pipe2[1]); // Close the write end of pipe 2 in the parent

        wait(NULL); // Wait for the child to finish

        exit(EXIT_SUCCESS);
    }

    return 0;
}
