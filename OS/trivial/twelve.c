// Write a program in C that creates a child process, waits for the termination of the child and lists its
// PID, together with the state in which the process was terminated (in decimal and hexadecimal).



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<fcntl.h>

int main() {
    pid_t child_pid;
    int status;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {  // Child process
        // Simulate some work in the child process
        for (int i = 0; i < 5; i++) {
            printf("Child process is working...\n");
            sleep(1);
        }
        exit(42); // Child exits with status 42
    } else {  // Parent process
        // Wait for the child process to terminate and get its status
        wait(&status);

        if (WIFEXITED(status)) {
            int child_exit_status = WEXITSTATUS(status);
            printf("Child PID: %d\n", child_pid);
            printf("Child terminated with exit status: %d (0x%X)\n", child_exit_status, child_exit_status);
        } else if (WIFSIGNALED(status)) {
            int term_signal = WTERMSIG(status);
            printf("Child PID: %d\n", child_pid);
            printf("Child terminated by signal: %d (0x%X)\n", term_signal, term_signal);
        }
    }

    return 0;
}
