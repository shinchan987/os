#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // it contains fork system call
#include <fcntl.h>


int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {  // Child process
        printf("Hello, world\n");
    } else {  // Parent process
        usleep(10000);  // Introduce a 10ms delay (adjust as needed)
        printf("Goodbye\n");
    }

    return 0;
}
