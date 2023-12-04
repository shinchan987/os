#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

// semaphore example
sem_t mutex;
void * routine(void *arg)
{
    printf("Process %d is Waiting for login\n",*(int*)arg);
    sem_wait(&mutex);
    printf("Process %d is loginned\n",*(int*)arg);
    sleep(2);
    printf("This is %d person\n",*(int*)arg);
    printf("Process %d is login out\n",*(int*)arg);
    sem_post(&mutex);

}
int main()
{
    pthread_t arr[5];
    sem_init(&mutex,0,1);
   
    for(int i=0;i<5;i++)
    {
        int *a=malloc(sizeof(int));
        *a=i;
        pthread_create(&arr[i],NULL,routine,a);

    }
    for(int i=0;i<5;i++)
    {
        pthread_join(arr[i],NULL);
    }

}
