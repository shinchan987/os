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








/*
 * C program to implement priority scheduling
 */
 
// #include <stdio.h>
 
// //Function to swap two variables
// void swap(int *a,int *b)
// {
//     int temp=*a;
//     *a=*b;
//     *b=temp;
// }
// int main()
// {
//     int n;
//     printf("Enter Number of Processes: ");
//     scanf("%d",&n);
 
//     // b is array for burst time, p for priority and index for process id
//     int b[n],p[n],index[n];
//     for(int i=0;i<n;i++)
//     {
//         printf("Enter Burst Time and Priority Value for Process %d: ",i+1);
//         scanf("%d %d",&b[i],&p[i]);
//         index[i]=i+1;
//     }
//     for(int i=0;i<n;i++)
//     {
//         int a=p[i],m=i;
 
//         //Finding out highest priority element and placing it at its desired position
//         for(int j=i;j<n;j++)
//         {
//             if(p[j] > a)
//             {
//                 a=p[j];
//                 m=j;
//             }
//         }
 
//         //Swapping processes
//         swap(&p[i], &p[m]);
//         swap(&b[i], &b[m]);
//         swap(&index[i],&index[m]);
//     }
 
//     // T stores the starting time of process
//     int t=0;
 
//     //Printing scheduled process
//     printf("Order of process Execution is\n");
//     for(int i=0;i<n;i++)
//     {
//         printf("P%d is executed from %d to %d\n",index[i],t,t+b[i]);
//         t+=b[i];
//     }
//     printf("\n");
//     printf("Process Id     Burst Time   Wait Time    TurnAround Time\n");
//     int wait_time=0;
//     for(int i=0;i<n;i++)
//     {
//         printf("P%d          %d          %d          %d\n",index[i],b[i],wait_time,wait_time + b[i]);
//         wait_time += b[i];
//     }
//     return 0;
// }
