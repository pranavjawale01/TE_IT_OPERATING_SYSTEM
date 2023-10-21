// Thread synchronization using counting semaphores. Application to demonstrate: producer- consumer problem with counting semaphores and mutex.	

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int buffer[5];
int in, out;
sem_t s, f, e;

void* producer(void* arg)
{
    sem_wait(&e);
    sem_wait(&s);
    int data;
    printf("\nEnter the Value ");
    scanf("%d", &data);
    buffer[in] = data;
    printf("Producer Thread id = %ld and Producer Item = %d", pthread_self(), data);sem_post(&s);     sem_post(&f);      sleep(2);
    in = (in + 1) % 5;
    sem_post(&s);
    sem_post(&f); 
    sleep(2);
}

void* consumer(void* arg)
{
    int conti = 0;
    do
    {
        sem_wait(&f);
        sem_wait(&s);
        int val = buffer[out];
        printf("\nConsumer Thread id = %ld and Consumer Item = %d", pthread_self(), val);
        out = (out + 1) % 5;
        sem_post(&s);
        sem_post(&e);
        sem_getvalue(&e, &conti);
    } while (conti != 5);
}

int main()
{
    pthread_t p_tid[5], c_tid;

    sem_init(&s, 0, 1);
    sem_init(&e, 0, 5);
    sem_init(&f, 0, 0);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&p_tid[i], NULL, producer, NULL);
    }
    pthread_create(&c_tid, NULL, consumer, NULL);

    for (int i = 0; i < 5; i++)
    {
        pthread_join(p_tid[i], NULL);
    }
    pthread_join(c_tid, NULL);

    return 0;
}






// Output :
// pranav@LAPTOP-TB69H925:~/TIA28$ gcc producerconsumer.c -lpthread
// pranav@LAPTOP-TB69H925:~/TIA28$ ./a.out

// Enter the Value 5
// Producer Thread id = 140583908443712 and Producer Item = 5
// Consumer Thread id = 140583792268864 and Consumer Item = 5
// Enter the Value 2
// Producer Thread id = 140583891658304 and Producer Item = 2
// Enter the Value 9
// Producer Thread id = 140583809054272 and Producer Item = 9
// Enter the Value 1
// Producer Thread id = 140583800661568 and Producer Item = 1
// Enter the Value 0
// Producer Thread id = 140583900051008 and Producer Item = 0
// Consumer Thread id = 140583792268864 and Consumer Item = 2
// Consumer Thread id = 140583792268864 and Consumer Item = 9
// Consumer Thread id = 140583792268864 and Consumer Item = 1
// Consumer Thread id = 140583792268864 and Consumer Item = 0
// pranav@LAPTOP-TB69H925:~/TIA28$