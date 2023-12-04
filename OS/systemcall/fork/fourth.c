#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This code is executed by the child process

        // Use execlp to replace the child process with the "ls" command
        execlp("ls", "ls", "-l", NULL);

        // If execlp fails, perror is executed
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // This code is executed by the parent process

        printf("Parent process (PID: %d) waiting for the child process (PID: %d) to finish.\n", getpid(), child_pid);

        // Wait for the child process to finish
        wait(NULL);

        printf("Parent process exiting.\n");
    }

    return 0;
}
