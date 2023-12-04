// producer consumer problem

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

// empty goes from n to 0;
// full goes from 0 to n

// Function prototypes
void* producer(void* arg);
void* consumer(void* arg);
void insert_item(int item);
int remove_item();

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create threads for producer and consumer
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

void* producer(void* arg) {
    int item;
    while (1) {
        // Produce an item
        item = rand() % 100;

        // Wait if the buffer is full
        sem_wait(&empty);
        // Wait to access the buffer
        sem_wait(&mutex);

        // Insert the item into the buffer
        printf("Item Produced\n");
        insert_item(item);

        // Signal that the buffer is no longer empty
        sem_post(&mutex);
        sem_post(&full);

        // Simulate some work
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        // Wait if the buffer is empty
        sem_wait(&full);
        // Wait to access the buffer
        sem_wait(&mutex);

        // Remove an item from the buffer
        item = remove_item();

        // Signal that the buffer is no longer full
        sem_post(&mutex);
        sem_post(&empty);

        // Consume the item
        printf("Consumed: %d\n", item);

        // Simulate some work
        sleep(2);
    }
}

void insert_item(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

int remove_item() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}
