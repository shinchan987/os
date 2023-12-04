// We want to synchronize process A with process B such that process A is not allowed to start
// iteration „i‟ before process B has terminated its own iteration „i-1‟.
// a. Write a program to implement this synchronization using a semaphore.



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Define a semaphore
sem_t semaphore;

// Shared variable to track the iteration
int iteration = 0;

// Function prototypes
void* processA(void* arg);
void* processB(void* arg);

int main() {
    // Initialize the semaphore
    sem_init(&semaphore, 0, 0); // Second parameter is 0 to indicate it's a local semaphore

    // Create threads for Process A and Process B
    pthread_t threadA, threadB;

    pthread_create(&threadA, NULL, processA, NULL);
    pthread_create(&threadB, NULL, processB, NULL);

    // Wait for threads to finish

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}

void* processA(void* arg) {
    for (int i = 0; i < 5; ++i) {
        // Wait for Process B to finish the previous iteration
        sem_wait(&semaphore);
        // Critical section for Process A
        printf("Process A - Iteration %d\n", i);
        
        // Signal Process B to start the next iteration
        sem_post(&semaphore);
        sleep(1);

    }

    pthread_exit(NULL);
}

void* processB(void* arg) {
    for (int i = 0; i < 5; ++i) {
        sem_post(&semaphore);
        printf("Process B - Iteration %d\n", i);
        sleep(1);
        sem_wait(&semaphore);
    }

    pthread_exit(NULL);
}
