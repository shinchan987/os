#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void customSignalHandler(int signum) {
    printf("Custom signal handler: Received SIGHUP (%d)\n", signum);
    // Additional actions can be performed here
}

int main() {
    struct sigaction sa;

    sa.sa_handler = customSignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        perror("Error installing signal handler for SIGHUP");
        exit(EXIT_FAILURE);
    }

    printf("Main program: Waiting for SIGHUP signal...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
