#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int burst_time;   // Burst time
    int remaining_time; // Remaining time to complete the process
};

// Function to perform Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int time_slice = (processes[i].remaining_time > time_quantum) ? time_quantum : processes[i].remaining_time;

                // Execute the process for a time slice
                processes[i].remaining_time -= time_slice;
                current_time += time_slice;

                printf("Process %d runs for time slice %d\n", processes[i].pid, time_slice);

                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                    printf("Process %d completed at time %d\n", processes[i].pid, current_time);
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int time_quantum;

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, time_quantum);

    return 0;
}
