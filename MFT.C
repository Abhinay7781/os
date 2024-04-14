

#include <stdio.h>
#include <stdbool.h>

// Partition structure
struct Partition {
    int pid;
    int size;
    char status[5]; // 'free' or 'occupied'
};

// Function to allocate memory to a process
bool allocate_memory(struct Partition partitions[], int num_partitions, int process_pid, int process_size) {
    for (int i = 0; i < num_partitions; i++) {
        if (strcmp(partitions[i].status, "free") == 0 && partitions[i].size >= process_size) {
            partitions[i].pid = process_pid;
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
            partitions[i].pid = -1;
            strcpy(partitions[i].status, "free");
            break;
        }
    }
}

int main() {
    // Initialize memory partitions
    struct Partition partitions[] = {
        { .pid = -1, .size = 64, .status = "free" },
        { .pid = -1, .size = 128, .status = "free" },
        { .pid = -1, .size = 256, .status = "free" }
    };
    int num_partitions = sizeof(partitions) / sizeof(partitions[0]);

    // Simulate processes
    struct {
        int pid;
        int size;
    } processes[] = {
        { 1, 100 },
        { 2, 64 },
        { 3, 200 }
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    // Allocate memory to processes
    for (int i = 0; i < num_processes; i++) {
        if (allocate_memory(partitions, num_partitions, processes[i].pid, processes[i].size)) {
            printf("Process %d allocated memory\n", processes[i].pid);
        } else {
            printf("Unable to allocate memory for process %d\n", processes[i].pid);
        }
    }

    // Deallocate memory as processes terminate
    deallocate_memory(partitions, num_partitions, 1);
    deallocate_memory(partitions, num_partitions, 2);

    return 0;
}
