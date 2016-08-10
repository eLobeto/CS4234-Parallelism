#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void* estimate_pi(void* rank);

//global variables
long long int num_tosses;
long long int num_in_circle;
int num_threads;
int sums_per_thread;
double pi_estimate;
pthread_mutex_t lock;

int main(int argc, char* argv[])
{
	//init variables
	num_tosses = strtoll(argv[1], NULL, 10);
	num_in_circle = 0;
	num_threads = 8;
	sums_per_thread = num_tosses/num_threads;
	pthread_mutex_init(&lock, NULL);

	//init threads
	pthread_t* thread_handles = malloc(num_threads * sizeof(pthread_t));
	long i;
	for(i = 0; i < num_threads; i++)
	{
		pthread_create(&thread_handles[i], NULL, estimate_pi, (void *) i);
	}

	//join threads
	for(i = 0; i < num_threads; i++)
	{
		pthread_join(thread_handles[i], NULL);
	}

	//print pi estimate
	pi_estimate = 4*num_in_circle/((double) num_tosses);
	printf("%f\n", pi_estimate);

	//free threads
	free(thread_handles);
}

void* estimate_pi(void* rank)
{
	long my_rank = (long) rank;
	int start = my_rank * sums_per_thread;
	int end = start + sums_per_thread;

	//create random number generator
	struct drand48_data rand_buff;
	srand48_r(time(NULL), &rand_buff);

	long my_num_in_circle = 0;
	long i;
	double x = 0;
	double y = 0;
	double distance_squared = 0;
	for(i = start; i < end; i++)
	{
		drand48_r(&rand_buff, &x);
		x = (x - .5) * 2;
		drand48_r(&rand_buff, &y);
		y = (y - .5) * 2;
		distance_squared = x*x + y*y;
		if(distance_squared <= 1)
			my_num_in_circle++;
	}

	//update global num in circle
	pthread_mutex_lock(&lock);
	num_in_circle += my_num_in_circle;
	pthread_mutex_unlock(&lock);
}