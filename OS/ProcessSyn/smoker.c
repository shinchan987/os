// To solve the Smoker problem, you can use a combination of mutex locks and condition variables
//  to synchronize the agent and the smokers. Here's a simple implementation in C using pthreads:



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t agent_ready, smoker_ready[3];

int available[3] = {0};  // 0: tobacco, 1: paper, 2: matches

void *agent_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        int ingredient1 = rand() % 3;
        int ingredient2;
        do {
            ingredient2 = rand() % 3;
        } while (ingredient1 == ingredient2);

        // Put the ingredients on the table
        available[ingredient1] = 1;
        available[ingredient2] = 1;

        printf("Agent puts %s and %s on the table.\n", (ingredient1 == 0) ? "tobacco" : (ingredient1 == 1) ? "paper" : "matches",
               (ingredient2 == 0) ? "tobacco" : (ingredient2 == 1) ? "paper" : "matches");

        // Signal the smoker who can now smoke
        pthread_cond_signal(&smoker_ready[(ingredient1 + ingredient2) % 3]);

        // Wait for the smoker to finish
        pthread_cond_wait(&agent_ready, &mutex);

        pthread_mutex_unlock(&mutex);

        // Simulate some time passing before the next round
        usleep(rand() % 1000000);
    }
}

void *smoker_thread(void *arg) {
    int smoker_id = *((int *)arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait for the necessary ingredients to be placed on the table
        while (!available[smoker_id]) {
            pthread_cond_wait(&smoker_ready[smoker_id], &mutex);
        }

        // Pick up the ingredients and make a cigarette
        available[smoker_id] = 0;
        printf("Smoker %d picks up the ingredients and rolls a cigarette.\n", smoker_id);

        // Signal the agent that smoking is done
        pthread_cond_signal(&agent_ready);

        pthread_mutex_unlock(&mutex);

        // Smoke the cigarette
        printf("Smoker %d smokes the cigarette.\n", smoker_id);
        usleep(rand() % 1000000);
    }
}

int main() {
    pthread_t agent, smokers[3];
    int smoker_ids[3] = {0, 1, 2};

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&agent_ready, NULL);
    for (int i = 0; i < 3; ++i) {
        pthread_cond_init(&smoker_ready[i], NULL);
    }

    pthread_create(&agent, NULL, agent_thread, NULL);

    for (int i = 0; i < 3; ++i) {
        pthread_create(&smokers[i], NULL, smoker_thread, (void *)&smoker_ids[i]);
    }

    pthread_join(agent, NULL);

    for (int i = 0; i < 3; ++i) {
        pthread_join(smokers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&agent_ready);
    for (int i = 0; i < 3; ++i) {
        pthread_cond_destroy(&smoker_ready[i]);
    }

    return 0;
}
