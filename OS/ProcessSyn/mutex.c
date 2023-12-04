// implemenatation of semaphore using mutex

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int semaphore_count = 1;  // Initial value of the semaphore

void wait_semaphore() {
    pthread_mutex_lock(&mutex);
    while (semaphore_count <= 0) {
        // If the semaphore is not available, wait
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    semaphore_count--;
    pthread_mutex_unlock(&mutex);
}

void signal_semaphore() {
    pthread_mutex_lock(&mutex);
    semaphore_count++;
    pthread_mutex_unlock(&mutex);
}

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    wait_semaphore();

    // Critical Section
    printf("Thread %d is in the critical section.\n", thread_id);
    // Simulate some work
    usleep(rand() % 1000000);

    signal_semaphore();

    // Non-critical Section
    printf("Thread %d is in the non-critical section.\n", thread_id);
    // Simulate some work
    usleep(rand() % 1000000);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1, 2, 3, 4};

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
