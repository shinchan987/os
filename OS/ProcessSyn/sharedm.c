// 3. Write a program where a parent process creates a shared memory and writes 1000 in a variable in the
// shared memory before creating 2 children processes A and B. After that, the parent waits for children
// termination and destroys the shared memory segment. Each child process performs 5 iterations. Every
// iteration process A adds 200 to the shared variable, and process B adds 100 to the shared variable. To
// help race conditions appear, both processes sleep for a random amount of time between the time they
// read the shared variable and the time they write back the shared variable after modification.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHARED_MEMORY_KEY 1234

typedef struct {
    int shared_variable;
} SharedData;

void processA(SharedData *shared_data) {
    for (int i = 0; i < 5; ++i) {
        usleep(rand() % 1000000); // Sleep for a random amount of time

        int temp = shared_data->shared_variable;
        printf("Process A read: %d\n", temp);

        usleep(rand() % 1000000); // Sleep for a random amount of time

        temp += 200;
        shared_data->shared_variable = temp;
        printf("Process A wrote: %d\n", temp);
    }
}

void processB(SharedData *shared_data) {
    for (int i = 0; i < 5; ++i) {
        usleep(rand() % 1000000); // Sleep for a random amount of time

        int temp = shared_data->shared_variable;
        printf("Process B read: %d\n", temp);

        usleep(rand() % 1000000); // Sleep for a random amount of time

        temp += 100;
        shared_data->shared_variable = temp;
        printf("Process B wrote: %d\n", temp);
    }
}

int main() {
    int shm_id = shmget(SHARED_MEMORY_KEY, sizeof(SharedData), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    SharedData *shared_data = (SharedData *)shmat(shm_id, NULL, 0);
    if ((int)shared_data == -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize the shared variable to 1000
    shared_data->shared_variable = 1000;

    pid_t pidA, pidB;

    if ((pidA = fork()) == 0) {
        // Child process A
        processA(shared_data);
        exit(EXIT_SUCCESS);
    } else if ((pidB = fork()) == 0) {
        // Child process B
        processB(shared_data);
        exit(EXIT_SUCCESS);
    } else if (pidA == -1 || pidB == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Wait for child processes to terminate
    waitpid(pidA, NULL, 0);
    waitpid(pidB, NULL, 0);

    // Output the final value of the shared variable
    printf("Final shared variable value: %d\n", shared_data->shared_variable);

    // Detach and destroy the shared memory
    shmdt(shared_data);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
