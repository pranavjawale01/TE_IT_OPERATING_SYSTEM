// Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) with different arrival time.	

#include<stdio.h>
#include<stdlib.h>

struct Process 
{
    int id;
    int arrival_time;
    int service_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

void shortestJobFirst(struct Process processes[], int n) 
{
    int currentTime = 0;
    int completed = 0;
    int shortest;

    while (completed < n) 
    {
        shortest = -1;
        int minServiceTime = INT_MAX;

        for (int i = 0; i < n; i++) 
        {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0 && processes[i].service_time < minServiceTime) 
            {
                shortest = i;
                minServiceTime = processes[i].service_time;
            }
        }

        if (shortest == -1) 
        {
            currentTime++;
        } 
        else 
        {
            processes[shortest].remaining_time--;
            currentTime++;
            if (processes[shortest].remaining_time == 0) 
            {
                completed++;
                processes[shortest].turnaround_time = currentTime - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].service_time;
            }
        }
    }
}

int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time and service time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter service time for process %d: ", i + 1);
        scanf("%d", &processes[i].service_time);
        processes[i].remaining_time = processes[i].service_time;
    }

    shortestJobFirst(processes, n);

    printf("Process\tArrival Time\tService Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].service_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate average waiting time and average turnaround time
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) 
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}


// Output >>

// Enter the number of processes: 5
// Enter arrival time for process 1: 0
// Enter service time for process 1: 3
// Enter arrival time for process 2: 2
// Enter service time for process 2: 6
// Enter arrival time for process 3: 4
// Enter service time for process 3: 4
// Enter arrival time for process 4: 6
// Enter service time for process 4: 5
// Enter arrival time for process 5: 8
// Enter service time for process 5: 2
// Process Arrival Time    Service Time    Waiting Time    Turnaround Time       
// 1       0               3               0               3
// 2       2               6               12              18
// 3       4               4               0               4
// 4       6               5               4               9
// 5       8               2               0               2
// Average Waiting Time: 3.20
// Average Turnaround Time: 7.20
// PS P:\VsCode> 