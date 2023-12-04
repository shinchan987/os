#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time; // Remaining time to complete the process
};

// Function to find the process with the shortest burst time
int findShortestJob(struct Process processes[], int n, int currentTime) {
    int shortestJob = -1;
    int shortestBurst = 999999; // A high value as initial shortest burst

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= currentTime && processes[i].remaining_time < shortestBurst && processes[i].remaining_time > 0) {
            shortestJob = i;
            shortestBurst = processes[i].remaining_time;
        }
    }

    return shortestJob;
}

// Function to calculate waiting time and turnaround time for each process
void findWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int shortestJob = findShortestJob(processes, n, currentTime);
        if (shortestJob == -1) {
            break; // No eligible process found at this time
        }

        // Update remaining time for the selected process
        processes[shortestJob].remaining_time -= 1;

        // Update waiting time for all other processes
        for (int j = 0; j < n; j++) {
            if (j != shortestJob && processes[j].arrival_time <= currentTime && processes[j].remaining_time > 0) {
                waiting_time[j] += 1;
            }
        }

        currentTime += 1;
    }
}

// Function to calculate turnaround time for each process
void findTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

// Function to calculate the average waiting time and average turnaround time
void findAverageTime(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    findWaitingTime(processes, n, waiting_time);
    findTurnaroundTime(processes, n, waiting_time, turnaround_time);

    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    findAverageTime(processes, n);

    return 0;
}
