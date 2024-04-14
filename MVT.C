

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Process structure
struct Process {
    int pid;
    int size;
};

// Partition structure
struct Partition {
    int pid;
    int size;
    char status[6]; // 'free' or 'occupied'
};

// Function to allocate memory to a process
bool allocate_memory(struct Partition partitions[], int num_partitions, struct Process process) {
    for (int i = 0; i < num_partitions; i++) {
        if (strcmp(partitions[i].status, "free") == 0 && partitions[i].size >= process.size) {
            partitions[i].pid = process.pid;
            strcpy(partitions[i].status, "occupied");
            return true;
        }
    }
    return false;
}

// Function to deallocate memory as processes terminate
void deallocate_memory(struct Partition partitions[], int num_partitions, int pid) {
    for (int i = 0; i < num_partitions; i++) {
        if (partitions[i].pid == pid) {
            partitions[i].pid = -1; // Change pid to -1 to indicate free partition
            strcpy(partitions[i].status, "free");
            break;
        }
    }
}

int main() {
    // Initialize memory partitions
    int num_partitions;
    printf("Enter the number of memory partitions: ");
    scanf("%d", &num_partitions);

    struct Partition *partitions = (struct Partition *)malloc(num_partitions * sizeof(struct Partition));
    for (int i = 0; i < num_partitions; i++) {
        partitions[i].pid = -1;
        printf("Enter the size of partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
        strcpy(partitions[i].status, "free");
    }

    // Simulate processes
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    struct Process *processes = (struct Process *)malloc(num_processes * sizeof(struct Process));
    for (int i = 0; i < num_processes; i++) {
        printf("Enter the PID and size of process %d: ", i + 1);
        scanf("%d %d", &processes[i].pid, &processes[i].size);

        if (allocate_memory(partitions, num_partitions, processes[i])) {
            printf("Process %d allocated memory\n", processes[i].pid);
        } else {
            printf("Unable to allocate memory for process %d\n", processes[i].pid);
        }
    }

    // Deallocate memory as processes terminate
    int pid_to_deallocate;
    printf("Enter the PID of the process to deallocate: ");
    scanf("%d", &pid_to_deallocate);
    deallocate_memory(partitions, num_partitions, pid_to_deallocate);

    // Print final partition status
    printf("\nPartition status after deallocation:\n");
    for (int i = 0; i < num_partitions; i++) {
        printf("Partition %d: PID=%d, Size=%d, Status=%s\n", i + 1, partitions[i].pid, partitions[i].size, partitions[i].status);
    }

    free(partitions); // Free dynamically allocated memory
    free(processes);  // Free dynamically allocated memory

    return 0;
}
