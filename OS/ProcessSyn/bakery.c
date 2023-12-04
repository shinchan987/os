
// bakery.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int number[NUM_THREADS] = {0, 0};
int choosing[NUM_THREADS] = {0, 0};

void enter_critical_section(int thread_id) {
    choosing[thread_id] = 1;
    int max_number = 0;

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (number[i] > max_number) {
            max_number = number[i];
        }
    }

    number[thread_id] = max_number + 1;
    choosing[thread_id] = 0;

    for (int i = 0; i < NUM_THREADS; ++i) {
        while (choosing[i]) {
            // Wait while other thread is choosing
        }

        while ((number[i] != 0) && ((number[i] < number[thread_id]) || ((number[i] == number[thread_id]) && (i < thread_id)))) {
            // Wait while other threads have higher priority
        }
    }
}

void leave_critical_section(int thread_id) {
    number[thread_id] = 0;
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
