

// banker algorithm

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_RESOURCES 3
#define NUM_PROCESSES 5

int available[NUM_RESOURCES] = {10, 5, 7};  // Available resources
int max_claim[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};  // Maximum claim of each process
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};  // Resources currently allocated to each process

pthread_mutex_t mutex;

void print_state() {
    printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);
    printf("Allocation matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_safe_state(int process_id, int request[NUM_RESOURCES]) {
    int temp_available[NUM_RESOURCES];
    int temp_allocation[NUM_PROCESSES][NUM_RESOURCES];

    // Copy the current state
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        temp_available[i] = available[i] - request[i];
    }
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            temp_allocation[i][j] = allocation[i][j];
        }
    }

    // Simulate resource allocation and check for safety
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        temp_available[i] += request[i];
        temp_allocation[process_id][i] -= request[i];
    }

    int finish[NUM_PROCESSES] = {0};
    int work[NUM_RESOURCES];

    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = temp_available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        int found = 0;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < NUM_RESOURCES; ++j) {
                    if (temp_allocation[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == NUM_RESOURCES) {
                    for (int k = 0; k < NUM_RESOURCES; ++k) {
                        work[k] += temp_allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    return count == NUM_PROCESSES;
}

void *process_thread(void *arg) {
    int process_id = *((int *)arg);
    int request[NUM_RESOURCES];

    while (1) {
        // Generate a random request
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            request[i] = rand() % (max_claim[process_id][i] - allocation[process_id][i] + 1);
        }

        // Request resources
        pthread_mutex_lock(&mutex);

        // Check if the request can be granted
        if (is_safe_state(process_id, request)) {
            printf("Process %d requesting resources: %d %d %d\n", process_id, request[0], request[1], request[2]);

            // Simulate resource allocation
            for (int i = 0; i < NUM_RESOURCES; ++i) {
                available[i] -= request[i];
                allocation[process_id][i] += request[i];
            }

            print_state();

            // Simulate resource release
            for (int i = 0; i < NUM_RESOURCES; ++i) {
                available[i] += request[i];
                allocation[process_id][i] -= request[i];
            }
        } else {
            printf("Process %d's request cannot be granted.\n", process_id);
        }

        pthread_mutex_unlock(&mutex);

        usleep(rand() % 1000000); // Simulating time passing before the next request
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t processes[NUM_PROCESSES];
    int process_ids[NUM_PROCESSES];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        process_ids[i] = i;
        pthread_create(&processes[i], NULL, process_thread, (void *)&process_ids[i]);
    }

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        pthread_join(processes[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}




// 1. Let Work and Finish be vectors of length m and n, respectively.
// Initialize:
// Work = Available
// Finish [i] = false for i = 0, 1, …, n- 1
// 2. Find an i such that both:
// (a) Finish [i] = false
// (b) Need i<Work
// If no such i exists, go to step 4
// 3. Work = Work + Allocation i
// Finish[i] = true
// go to step 2
// 4. If Finish [i] == true for all i, then the system is in a safe state


// Request i = request vector for process P i . If Request i [j] = k then
// process P i wants k instances of resource type R j
// 1. If Request i<Need i go to step 2. Otherwise, raise error
// condition, since process has exceeded its maximum claim
// 2. If Request i<Available, go to step 3. Otherwise P i must wait,
// since resources are not available
// 3. Pretend to allocate requested resources to P i by modifying the
// state as follows:
// Available = Available – Request i ;
// Allocation i = Allocation i + Request i ;
// Need i = Need i – Request i ;
// • If safe  the resources are allocated to P i
// • If unsafe  P i must wait, and the old resource-allocation state
// is restored


// detection

// work=available
// if allocatio(i)!=0 finish[i]=false
// find i such that finish[i]=false and request(i)<=work
// work+=allocaioni
// finis[i]=true