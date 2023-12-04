// Write a program that opens a file (with the open() system call) and then calls fork() to create a new
// process. Can both the child and parent access the file descriptor returned by open()? What happens
// when they are writing to the file concurrently, i.e., at the same time? Clearly write your
// observations.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>



int main() {
    int file_descriptor;
    pid_t child_pid;

    // Open a file for writing
    file_descriptor = open("example.txt", O_CREAT | O_WRONLY, 0644);

    if (file_descriptor == -1) {
        perror("Failed to open file");
        exit(1);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {  // Child process
        const char* message = "This is the child process writing to the file\n";
        write(file_descriptor, message, strlen(message));
    } else {  // Parent process
        const char* message = "This is the parent process writing to the file\n";
        write(file_descriptor, message, strlen(message));
    }

    close(file_descriptor);
    return 0;
}
