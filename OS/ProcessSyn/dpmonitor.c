#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond[NUM_PHILOSOPHERS];
    int is_eating[NUM_PHILOSOPHERS];
} Monitor;

Monitor monitor;

void init_monitor(Monitor *m) {
    pthread_mutex_init(&m->mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_cond_init(&m->cond[i], NULL);
        m->is_eating[i] = 0;
    }
}

void take_forks(Monitor *m, int philosopher_id) {
    pthread_mutex_lock(&m->mutex);
    m->is_eating[philosopher_id] = 1;
    pthread_mutex_unlock(&m->mutex);
}

void put_forks(Monitor *m, int philosopher_id) {
    pthread_mutex_lock(&m->mutex);
    m->is_eating[philosopher_id] = 0;
    pthread_cond_signal(&m->cond[(philosopher_id + 1) % NUM_PHILOSOPHERS]); // Signal right neighbor
    pthread_cond_signal(&m->cond[(philosopher_id - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS]); // Signal left neighbor
    pthread_mutex_unlock(&m->mutex);
}

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        usleep(rand() % 1000000); // Simulating thinking

        // Take forks
        take_forks(&monitor, philosopher_id);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        usleep(rand() % 1000000); // Simulating eating

        // Put forks
        put_forks(&monitor, philosopher_id);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    init_monitor(&monitor);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&philosopher_ids[i]);
    }

    // Join philosopher threads (this will never be reached in this example as the philosophers run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}





// monitor solution abstract
// monitor DiningPhilosophers
// {
//     enum { THINKING; HUNGRY, EATING) state [5] ;
//     condition self [5];
//     void pickup (int i) {
//         state[i] = HUNGRY;
//         test(i);
//         if (state[i] != EATING) self[i].wait;
//     }

//     void putdown (int i) {
//         state[i] = THINKING;
//         // test left and right neighbors
//         test((i + 4) % 5);
//         test((i + 1) % 5);
//     }

//     void test (int i) {
//         if ((state[(i + 4) % 5] != EATING) &&
//         (state[i] == HUNGRY) &&
//         (state[(i + 1) % 5] != EATING) ) {
//         state[i] = EATING ;
//         self[i].signal () ;
//     }
//     }
//     initialization_code() {
//         for (int i = 0; i < 5; i++)
//         state[i] = THINKING;
//     }
// }

// DiningPhilosophers.pickup(i) ;
// /** EAT **/
// DiningPhilosophers.putdown(i) ;


// monitor DiningPhilosophers {
//    enum {THINKING, HUNGRY, EATING} state[5];
//    condition self[5];
//    void pickup(int i) {
//       state[i] = HUNGRY;
//       test(i);
//       if (state[i] != EATING) {
//          self[i].wait();
//       }
//    }
//    void putdown(int i) {
//       state[i] = THINKING;
//       test((i + 4) % 5);
//       test((i + 1) % 5);
//    }
//    void test(int i) {
//       if (state[(i + 4) % 5] != EATING &&
//       state[i] == HUNGRY &&
//       state[(i + 1) % 5] != EATING) {
//          state[i] = EATING;
//          self[i].signal();
//       }
//    }
//    initialization code() {
//       for(int i=0;i<5;i++)
//       state[i] = THINKING;
//    }
// }
// DiningPhilosophers dp


// Only one process may be active within the monitor at a time

// Conditional variables provide synchronization inside the monitor. 
// If a process wants to sleep or it allows a waiting process to continue, 
// in that case conditional variables are used in monitors.
//  Two operations can be performed on the conditional variables: wait and signal
// wait() − Process invoking this operation is suspended and placed in block queue of that conditional variable.

// signal() − This operation resumes the suspended process.