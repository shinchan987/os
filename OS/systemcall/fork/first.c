#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    int status;

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This code is executed by the child process

        printf("Child process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        // Child process exits normally with status 42
        exit(42);
    } else {
        // This code is executed by the parent process

        printf("Parent process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", child_pid);

        // Wait for the child process to finish and get its exit status
        if (wait(&status) == -1) {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("Child process exited normally with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            // Check if the child process was terminated by a signal
            printf("Child process terminated by signal: %d\n", WTERMSIG(status));
        } else {
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}
