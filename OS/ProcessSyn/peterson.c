// peterson son solution

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int turn = 0;
int interested[NUM_THREADS] = {0, 0};

void enter_critical_section(int thread_id) {
    int other_thread = 1 - thread_id;  // Identify the other thread

    // Declare interest in the critical section
    interested[thread_id] = 1;

    // Set turn to the other thread and wait if it's their turn
    turn = other_thread;
    while (turn == other_thread && interested[other_thread] == 1) {
        // Busy-wait
    }
}

void leave_critical_section(int thread_id) {
    // Release interest in the critical section
    interested[thread_id] = 0;
}

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    for (int i = 0; i < 5; ++i) {
        enter_critical_section(thread_id);

        // Critical Section
        printf("Thread %d is in the critical section.\n", thread_id);
        // Simulate some work
        usleep(rand() % 1000000);

        leave_critical_section(thread_id);

        // Non-critical Section
        printf("Thread %d is in the non-critical section.\n", thread_id);
        // Simulate some work
        usleep(rand() % 1000000);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1};

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
