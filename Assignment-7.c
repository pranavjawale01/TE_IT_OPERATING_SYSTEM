// Thread synchronization and mutual exclusion using mutex. Application to demonstrate: Reader- Writer problem with reader priority.	

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int books[5];

sem_t r,w;
int readCount=0;


void rread()
{
	FILE *fptr;
	fptr = fopen("/home/pranav/TIA28/file.txt", "r");
	char myString[100];
	//fgets(myString, 100, fptr);
	while (fgets(myString, sizeof(myString), fptr) != NULL) 
	{
        	printf("%s", myString);
    	}
	//printf("%s", myString);
	fclose(fptr);
}

void wwrite()
{
	FILE *fptr;
	fptr = fopen("/home/pranav/TIA28/file.txt", "a");
	printf("\nEnter Some text to write \n");
	char text[100];
	scanf("%s",text);
	fprintf(fptr,"%s\n",text);
	fclose(fptr);
}


void* reading(void* arg)
{
	sem_wait(&r);
	readCount++;
	if(readCount==1)
	{
		sem_wait(&w);
	}
	sem_post(&r);
	printf("\nThread ID for Reading is  %ld with count %d\n",pthread_self(),readCount);
	rread();
	sem_wait(&r);
	readCount--;
	if(readCount==0)
	{
		sem_post(&w);
	}
	sem_post(&r);
	sleep(3);
}

void* writing(void* arg)
{
	sem_wait(&w);
	printf("\nThread ID for Writing is  %ld\n",pthread_self());
	wwrite();
	sem_post(&w);
	sleep(3);
}

int main()
{
	pthread_t write[5],read[5];
	
	sem_init(&w, 0, 1);
	sem_init(&r, 0, 1);
	
	for(int i=0;i<5;i++)
	{
		pthread_create(&write[i], NULL, reading, NULL);
		pthread_create(&read[i], NULL, writing, NULL);
	}
	for (int i=0;i<5;i++)
    {
    	pthread_join(write[i], NULL);
    	pthread_join(read[i], NULL);
    }
	
	return 0;
}

// Output :

// pranav@LAPTOP-TB69H925:~/TIA28$ gcc readwrite.c -lpthread
// pranav@LAPTOP-TB69H925:~/TIA28$ ./a.out

// Thread ID for Reading is  140697386092096 with count 1

// Thread ID for Reading is  140697235088960 with count 2

// Thread ID for Reading is  140697290143296 with count 2

// Thread ID for Writing is  140697377699392

// Enter Some text to write
// pranav

// Thread ID for Writing is  140697369306688

// Enter Some text to write
// abhi

// Thread ID for Writing is  140697281750592

// Enter Some text to write
// kshitij

// Thread ID for Reading is  140697273357888 with count 1

// Thread ID for Reading is  140697256572480 with count 2
// pranav
// abhi
// kshitij
// pranav
// abhi
// kshitij

// Thread ID for Writing is  140697264965184

// Enter Some text to write
// ayush

// Thread ID for Writing is  140697248179776

// Enter Some text to write
// Parth
// pranav@LAPTOP-TB69H925:~/TIA28$