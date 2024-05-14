#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 4999
#define REQUESTS 1000

// calculate the absolute diff between two integers
int abs_diff(int a, int b) {
    return abs(a - b);
}

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


// FCFS
int fcfs(int head, int requests[]) {
    int total_head_movements = 0;
    for (int i = 0; i < REQUESTS; i++) {
        total_head_movements += abs_diff(head, requests[i]);
        head = requests[i];
    }
    return total_head_movements;
}

// SCAN
int scan(int head, int requests[]) {
    int total_head_movements = 0;
    int direction = 1; // 1 for moving towards higher cylinders, -1 for lower cylinders
    int current_request_index = 0;

    qsort(requests, REQUESTS, sizeof(int), cmpfunc);

    while (current_request_index < REQUESTS && requests[current_request_index] < head) {
        current_request_index++;
    }

    for (int i = current_request_index; i < REQUESTS; i++) {
        total_head_movements += abs_diff(head, requests[i]);
        head = requests[i];
    }

    for (int i = current_request_index - 1; i >= 0; i--) {
        total_head_movements += abs_diff(head, requests[i]);
        head = requests[i];
    }

    return total_head_movements;
}

// C-SCAN
int cscan(int head, int requests[]) {
    int total_head_movements = 0;
    int current_request_index = 0;

    qsort(requests, REQUESTS, sizeof(int), cmpfunc);

    while (current_request_index < REQUESTS && requests[current_request_index] < head) {
        current_request_index++;
    }

    for (int i = current_request_index; i < REQUESTS; i++) {
        total_head_movements += abs_diff(head, requests[i]);
        head = requests[i];
    }
    total_head_movements += abs_diff(head, CYLINDERS - 1); // move to end
    head = 0; // move to beginning
    total_head_movements += CYLINDERS - 1;

    for (int i = 0; i < current_request_index; i++) {
        total_head_movements += abs_diff(head, requests[i]);
        head = requests[i];
    }

    return total_head_movements;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <initial_head_position> <requests_file>\n", argv[0]);
        return 1;
    }

    int initial_head_position = atoi(argv[1]);
    int requests[REQUESTS];
    FILE *file = fopen(argv[2], "r");

    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < REQUESTS; i++) {
        if (fscanf(file, "%d", &requests[i]) != 1) {
            printf("Error reading file.\n");
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    printf("Task 1:\n");
    printf("FCFS: %d\n", fcfs(initial_head_position, requests));
    printf("SCAN: %d\n", scan(initial_head_position, requests));
    printf("C-SCAN: %d\n", cscan(initial_head_position, requests));

    printf("\nTask 2:\n");

    // task 2 sorted
    int sorted_requests[REQUESTS];
    for (int i = 0; i < REQUESTS; i++) {
        sorted_requests[i] = requests[i];
    }

    // sorted requests
    qsort(sorted_requests, REQUESTS, sizeof(int), cmpfunc);

    printf("FCFS: %d\n", fcfs(initial_head_position, sorted_requests));
    printf("SCAN: %d\n", scan(initial_head_position, sorted_requests));
    printf("C-SCAN: %d\n", cscan(initial_head_position, sorted_requests));

    return 0;
}
