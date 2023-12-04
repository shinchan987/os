// . Write a program that uses wait() system call to wait for the child process to finish in the parent.
// What does wait() return? What happens if you use wait() in the child? Further, modify your code to
// use waitpid() instead of wait(). When would waitpid() be useful? Clearly write your observations

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    int status;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {  // Child process
        printf("Child: Hello, world\n");
    } else {  // Parent process
        waitpid(child_pid, &status, 0);
        printf("Parent: Goodbye\n");

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process was terminated by signal: %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
