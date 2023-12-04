// The Sleeping Barber problem is a classic synchronization problem that illustrates
//  issues with concurrent access and the need for proper synchronization mechanisms. 
//  The problem involves a barber who alternates between cutting hair and sleeping, 
//  and customers who enter a barbershop, 
// either wait if the barber is busy or wake up the barber if he is sleeping.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CHAIRS 5

pthread_mutex_t mutex;
pthread_cond_t barber_ready, customer_ready;
int customers_waiting = 0;
int barber_sleeping = 0;

void *barber_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        if (customers_waiting == 0) {
            // If no customers, barber sleeps
            printf("Barber is sleeping.\n");
            barber_sleeping = 1;
            pthread_cond_wait(&customer_ready, &mutex);
        }

        // Cutting hair
        printf("Barber is cutting hair.\n");
        customers_waiting--;
        barber_sleeping = 0;

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&barber_ready);

        // Simulate haircut
        usleep(rand() % 1000000);
    }
}

void *customer_thread(void *arg) {
    int customer_id = *((int *)arg);

    pthread_mutex_lock(&mutex);

    if (customers_waiting < NUM_CHAIRS) {
        // Customer enters the shop and waits if there are available chairs
        customers_waiting++;
        printf("Customer %d is waiting.\n", customer_id);

        if (barber_sleeping) {
            // Wake up the barber if sleeping
            printf("Barber is sleeping. Customer %d wakes up the barber.\n", customer_id);
            pthread_cond_signal(&customer_ready);
        }

        pthread_mutex_unlock(&mutex);
        pthread_cond_wait(&barber_ready, &mutex); // Wait for the barber to finish cutting hair
    } else {
        // If no available chairs, customer leaves
        printf("Customer %d leaves as no chairs are available.\n", customer_id);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t barber, customers[NUM_CHAIRS];
    int customer_ids[NUM_CHAIRS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&barber_ready, NULL);
    pthread_cond_init(&customer_ready, NULL);

    pthread_create(&barber, NULL, barber_thread, NULL);

    for (int i = 0; i < NUM_CHAIRS; ++i) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, customer_thread, (void *)&customer_ids[i]);
    }

    pthread_join(barber, NULL);

    for (int i = 0; i < NUM_CHAIRS; ++i) {
        pthread_join(customers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&barber_ready);
    pthread_cond_destroy(&customer_ready);

    return 0;
}
