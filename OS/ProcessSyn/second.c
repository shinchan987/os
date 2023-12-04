// semaphore

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;

void * routine(void * arg)
{
    sem_wait(&mutex);
    sleep(2);
    printf("This is routine %d\n",*(int*)arg);
    sem_post(&mutex);
    free(arg);
}
int main()
{
   pthread_t arr[4];
   sem_init(&mutex,0,1);
   for(int i=0;i<4;i++)
   {
    int* a=malloc(sizeof(int));
    *a=i;
    pthread_create(&arr[i],NULL,routine,a);
   }
   for(int i=0;i<4;i++)
   {
     pthread_join(arr[i],NULL);
   }
    return 0;
}
