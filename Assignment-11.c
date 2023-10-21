// Inter process communication in Linux using Shared Memory	

// 1:-
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    printf("Write Data : ");
    fgets(str, 1024, stdin);

    printf("Data written in memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    return 0;
}

// 2:-
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    printf("Data read from memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}



// OUTPUT >>

// Terminal 1
// pranav@pranav:~/OS/7B$ gcc u1.c
// pranav@pranav:~/OS/7B$ ./a.out
// Write Data : hello world
// Data written in memory: hello world

// Terminal 2
// pranav@pranav:~/OS/7B$ gcc u2.c
// pranav@pranav:~/OS/7B$ ./a.out
// Data read from memory: hello world