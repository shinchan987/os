



#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

// Function to find the waiting time for each process
void findWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    waiting_time[0] = 0; // The first process has a waiting time of 0

    for (int i = 1; i < n; i++) {
        // Waiting time for the current process is the sum of its burst time and the waiting time of the previous process
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }
}

// Function to find the turnaround time for each process
void findTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        // Turnaround time is the sum of burst time and waiting time for each process
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
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
    }

    findAverageTime(processes, n);

    return 0;
}
