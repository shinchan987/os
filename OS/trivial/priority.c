#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int burst_time;   // Burst time
    int priority;     // Priority value (lower value indicates higher priority)
    int completion_time; // Completion time
};

// Function to perform Priority scheduling
void priorityScheduling(struct Process processes[], int n) {
    // Sort the processes based on priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // Update the completion time for the current process
        processes[i].completion_time = current_time + processes[i].burst_time;

        // Update the current time
        current_time = processes[i].completion_time;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    printf("Process\tBurst Time\tPriority\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].completion_time);
    }

    return 0;
}
