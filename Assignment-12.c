// Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look considering the initial head position moving away from the spindle.	

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void shortestSeekTimeFirst(int request[], int head, int n) 
{
    int seek_sequence[n];
    int seek_count = 0;
    bool visited[n];

    for (int i = 0; i < n; i++) 
    {
        visited[i] = false;
    }

    for (int i = 0; i < n; i++) 
    {
        int min_distance = INT_MAX;
        int index = -1;
        for (int j = 0; j < n; j++) 
        {
            if (!visited[j] && abs(head - request[j]) < min_distance) 
            {
                index = j;
                min_distance = abs(head - request[j]);
            }
        }
        visited[index] = true;
        seek_sequence[i] = request[index];
        seek_count += min_distance;
        head = request[index];
    }

    printf("SSTF Disk Scheduling Algorithm:\n");
    printf("Total seek time: %d\n", seek_count);
    printf("Seek sequence: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n\n");
}

void scan(int request[], int head, int n, int direction, int disk_size) 
{
    int seek_sequence[n + 1];
    int seek_count = 0;
    int distance;
    int cur_track;

    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (request[i] > request[j]) 
            {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    int index;
    for (index = 0; index < n; index++) 
    {
        if (head < request[index]) 
        {
            break;
        }
    }

    int left = index - 1;
    int right = index;

    int seek_sequence_index = 0;

    // Handle right direction
    if(direction==1)
    {
        while (right < n) 
        {
            cur_track = request[right];
            distance = abs(cur_track - head);
            seek_count += distance;
            seek_sequence[seek_sequence_index++] = cur_track;
            head = cur_track;
            right++;
        }

        cur_track = disk_size-1;
        distance = abs(cur_track - head);
        seek_count += distance;
        seek_sequence[seek_sequence_index++] = cur_track;
        head = cur_track;

        while (left >= 0) 
        {
            cur_track = request[left];
            distance = abs(cur_track - head);
            seek_count += distance;
            seek_sequence[seek_sequence_index++] = cur_track;
            head = cur_track;
            left--;
        }
    }
    else if(direction==0)
    {
        while (left >= 0) 
        {
            cur_track = request[left];
            distance = abs(cur_track - head);
            seek_count += distance;
            seek_sequence[seek_sequence_index++] = cur_track;
            head = cur_track;
            left--;
        }

        cur_track = 0;
        distance = abs(cur_track - head);
        seek_count += distance;
        seek_sequence[seek_sequence_index++] = cur_track;
        head = cur_track;

        while (right < n) 
        {
            cur_track = request[right];
            distance = abs(cur_track - head);
            seek_count += distance;
            seek_sequence[seek_sequence_index++] = cur_track;
            head = cur_track;
            right++;
        }
    }

    printf("SCAN Disk Scheduling Algorithm:\n");
    printf("Total seek time: %d\n", seek_count);
    printf("Seek sequence: ");
    for (int i = 0; i <= n; i++) 
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n\n");
}

void cLook(int request[], int head, int n, int direction, int disk_size) 
{
    int seek_sequence[n];
    int seek_count = 0;
    int distance;
    int cur_track;

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (request[i] > request[j]) 
            {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    int index;
    for (index = 0; index < n; index++) 
    {
        if (head < request[index]) 
        {
            break;
        }
    }

    int left = index-1;
    int right = index;

    for (int i = 0; i < n; i++) 
    {
        if (direction == 0) 
        {
            if (left <= 0) 
            {
                cur_track = request[0];
                left = n-1;
            }
            else
            {
                cur_track = request[left];
                left--;
            }
        } 
        else if(direction == 1)
        {
            cur_track = request[right];
            right = (right + 1) % n;
        }
        distance = abs(cur_track - head);
        seek_sequence[i] = cur_track;
        head = cur_track;
        seek_count += distance;
    }

    printf("C-LOOK Disk Scheduling Algorithm:\n");
    printf("Total seek time: %d\n", seek_count);
    printf("Seek sequence: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n\n");
}

int main() 
{
    int n, head, direction;
    int disk_size = 200;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the Disk Size : ");
    scanf("%d",&disk_size);
    int proc[n];
    printf("Enter the requests: ");
    for(int i = 0; i < n; i++) 
    {
        scanf("%d", &proc[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (proc[i] > proc[j]) 
            {
                int temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    shortestSeekTimeFirst(proc, head, n);
    scan(proc, head, n, direction, disk_size);
    cLook(proc, head, n, direction, disk_size);

    return 0;
}


// OUTPUT >> 
// Enter the number of requests: 7
// Enter the Disk Size : 200
// Enter the requests: 82
// 170
// 43
// 140
// 24
// 16
// 190
// Enter the initial head position: 50
// Enter the direction (0 for left, 1 for right): 1
// SSTF Disk Scheduling Algorithm:
// Total seek time: 208
// Seek sequence: 43 24 16 82 140 170 190

// SCAN Disk Scheduling Algorithm:
// Total seek time: 332
// Seek sequence: 82 140 170 190 199 43 24 16

// C-LOOK Disk Scheduling Algorithm:
// Total seek time: 341
// Seek sequence: 82 140 170 190 16 24 43

// PS P:\VsCode> 