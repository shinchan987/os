// thread to copy from one file ans paste in other file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

// Structure to hold data for each thread
typedef struct {
    const char *input_file;
    const char *output_file;
} ThreadData;

// Function to read from input file and write to output file using system calls
void *file_copy(void *arg) {
    ThreadData *thread_data = (ThreadData *)arg;
    int input_fd, output_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Open input file
    if ((input_fd = open("input.txt", O_RDONLY)) == -1) {
        perror("Error opening input file");
        pthread_exit(NULL);
    }

    // Open output file
    if ((output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("Error opening output file");
        close(input_fd);
        pthread_exit(NULL);
    }

    // Read from input file and write to output file
    while ((bytesRead = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        write(output_fd, buffer, bytesRead);
    }

    // Close files
    close(input_fd);
    close(output_fd);

    pthread_exit(NULL);
}

int main() {
    pthread_t read_thread, write_thread;

    // Specify input and output file names
    const char *input_file = "input.txt";
    const char *output_file = "output.txt";

    // Create thread data structures
    ThreadData read_data = {input_file, NULL};
    ThreadData write_data = {NULL, output_file};

    // Create threads
    if (pthread_create(&read_thread, NULL, file_copy, (void *)&read_data) != 0) {
        perror("Error creating read thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&write_thread, NULL, file_copy, (void *)&write_data) != 0) {
        perror("Error creating write thread");
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    if (pthread_join(read_thread, NULL) != 0) {
        perror("Error joining read thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(write_thread, NULL) != 0) {
        perror("Error joining write thread");
        exit(EXIT_FAILURE);
    }

    printf("File copy completed successfully!\n");

    return 0;
}
