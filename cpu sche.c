#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int pid;
    int burst_time;
    int priority;
    int arrival_time;
};

// Function to perform priority scheduling
void priority_scheduling(struct Process processes[], int n) {
    // Sort the processes based on priority
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
    int waiting_time = 0;
    int turnaround_time = 0;

    printf("PID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        waiting_time += current_time - processes[i].arrival_time;
        turnaround_time += waiting_time + processes[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
               processes[i].priority, waiting_time, turnaround_time);
        current_time += processes[i].burst_time;
    }

    double avg_waiting_time = (double)waiting_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

// Example usage
int main() {
    struct Process processes[] = {
        {1, 10, 3, 0},
        {2, 5, 1, 0},
        {3, 8, 2, 0} 
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    priority_scheduling(processes, n);
    return 0;
}
