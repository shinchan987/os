#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>

void customSignalHandler(int signum) {
    printf("Custom signal handler: Received signal %d (SIGINT)\n", signum);
   
}

int main() { // Additional actions can be performed here
    // Create a struct for the sigaction
    struct sigaction sa;

    // Initialize the sigaction struct
    sa.sa_handler = customSignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Install the custom signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error installing signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Main program: Waiting for a signal...\n");

    // Infinite loop to keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}
