// CPP code to search for element in a
// very large file using Multithreading
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Max size of array
#define max 16

// Max number of threads to create
#define thread_max 4

int a[max] = { 1, 5, 7, 10, 12, 14, 15, 18,
			20, 22, 25, 27, 30, 64, 110, 220 };
int key = 202;

// Flag to indicate if key is found in a[]
// or not.
int f = 0;

int current_thread = 0;

// Linear search function which will
// run for all the threads
void* ThreadSearch(void* args)
{
	int num = current_thread++;

	for (int i = num * (max / 4);
		i < ((num + 1) * (max / 4)); i++) {
		if (a[i] == key)
			f = 1;
	}
}

// Driver Code
int main()
{
	pthread_t thread[thread_max];

	for (int i = 0; i < thread_max; i++) {
		pthread_create(&thread[i], NULL, ThreadSearch,
					(void*)NULL);
	}

	for (int i = 0; i < thread_max; i++) {
		pthread_join(thread[i], NULL);
	}

	if (f == 1)
		// cout << "Key element found" << endl;
        printf("Key found\n");
	else
		printf("Key Not found\n");
	return 0;
}