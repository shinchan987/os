#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Structure to hold data for each thread
typedef struct {
    int pipe_fd[2];  // Pipe file descriptors
} ThreadData;

// Function for the first thread to write data to the pipe
void *write_thread(void *arg) {
    ThreadData *thread_data = (ThreadData *)arg;
    char buffer[BUFFER_SIZE] = "Hello from the write thread!";

    // Close read end of the pipe since we are writing
    close(thread_data->pipe_fd[0]);

    // Write data to the pipe
    write(thread_data->pipe_fd[1], buffer, sizeof(buffer));

    // Close write end of the pipe
    close(thread_data->pipe_fd[1]);

    pthread_exit(NULL);
}

// Function for the second thread to read data from the pipe
void *read_thread(void *arg) {
    ThreadData *thread_data = (ThreadData *)arg;
    char buffer[BUFFER_SIZE];

    // Close write end of the pipe since we are reading
    close(thread_data->pipe_fd[1]);

    // Read data from the pipe
    read(thread_data->pipe_fd[0], buffer, sizeof(buffer));

    // Close read end of the pipe
    close(thread_data->pipe_fd[0]);

    // Print the received data
    printf("Received from the pipe: %s\n", buffer);

    pthread_exit(NULL);
}

int main() {
    pthread_t write_thread_id, read_thread_id;
    ThreadData thread_data;
    printf("a\n");
    // Create a pipe
    if (pipe(thread_data.pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create threads
    if (pthread_create(&write_thread_id, NULL, write_thread, (void *)&thread_data) != 0) {
        perror("Error creating write thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&read_thread_id, NULL, read_thread, (void *)&thread_data) != 0) {
        perror("Error creating read thread");
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    if (pthread_join(write_thread_id, NULL) != 0) {
        perror("Error joining write thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(read_thread_id, NULL) != 0) {
        perror("Error joining read thread");
        exit(EXIT_FAILURE);
    }

    printf("Threads communication using pipes completed successfully!\n");

    return 0;
}
