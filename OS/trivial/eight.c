// Write a program that uses wait() system call to wait for the child process to finish in the parent.
// What does wait() return? What happens if you use wait() in the child? Further, modify your code to
// use waitpid() instead of wait(). When would waitpid() be useful? Clearly write your observations.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, wait_result;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {  // Child process
        printf("Child: Hello, world\n");
    } else {  // Parent process
        wait_result = wait(NULL);
        printf("Parent: Goodbye\n");

        if (wait_result == -1) {
            perror("Wait failed");
            return 1;
        }
    }

    return 0;
}
