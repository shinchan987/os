#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void ignoreSignalHandler(int signum) {
    printf("Ignoring signal %d\n", signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = ignoreSignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error installing signal handler for SIGUSR1");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Error installing signal handler for SIGUSR2");
        exit(EXIT_FAILURE);
    }
    printf("Main program: Waiting for signals...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
