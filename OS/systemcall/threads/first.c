// CPP Program to find sum of array 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// size of array 
#define MAX 16 

// maximum number of threads 
#define MAX_THREAD 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 }; 
int sum[4] = { 0 }; 
int part = 0; 

void* sum_array(void* arg) 
{ 
	int thread_part = part++; 

	for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) 
		sum[thread_part] += a[i]; 
} 

// gcc -pthread first.c
// cc -lpthread pthread1.c
int main() 
{ 

	pthread_t threads[MAX_THREAD]; 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_create(&threads[i], NULL, sum_array, (void*)NULL); 


	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL); 

	int total_sum = 0; 
	for (int i = 0; i < MAX_THREAD; i++) 
		total_sum += sum[i]; 
    printf("%d\n",total_sum);

	return 0; 