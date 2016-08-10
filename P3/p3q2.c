#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_FILE_NAME_LENGTH 128
#define MAX_LINE_LENGTH 1024

void produce(int x);
void consume();
void frontelement(char* dest);
void enq(char* data);
void deq(char* dest);
int empty();
void create();
void queuesize();

struct node
{
    char* info;
    struct node *ptr;
}*front,*rear,*temp,*front1;

int num_producers, num_consumers;
char** files;
omp_lock_t lock;
int count, max_queue_size, prod_count;
FILE* output;

int main(int argc, char* argv[])
{
	//usage is num producers, num consumers, max queue size
	//producers must be < consumers
	num_producers = strtol(argv[1], NULL, 10);
	num_consumers = strtol(argv[2], NULL, 10);
	max_queue_size = strtol(argv[3], NULL, 10);

	//set up producer file name array
	files = malloc(num_producers * sizeof(char*));
	int x;
	for(x = 0; x < num_producers; x++)
	{
		files[x] = malloc(MAX_FILE_NAME_LENGTH * sizeof(char));
	}

	int i;
	for(i = 0; i < num_producers; i++)
	{
		printf("Enter file for producer %d: \n", i);
		//allow user to input file names for each producer
		scanf("%s", files[i]);
	}

	//init lock
	omp_init_lock(&lock);

	//init queue
	create();

	//open file to output to
	output = fopen("output.txt", "w");
	prod_count = 0;

	//launch producers and consumers
	int q;
	#pragma omp parallel for
	for(q = 0; q < num_producers + num_consumers; q++)
	{
		if(q < num_producers)
		{
			printf("producer and consumer %d\n", q);
			produce(q);
			consume();
		}
		else if(q >= num_producers && q < num_consumers)
		{
			printf("consumer %d\n", q);
			consume();
		}
	}

	fclose(output);
}

void produce(int x)
{
	int my_rank = x;

	FILE *infile;
	infile = fopen(files[my_rank], "r");

	char line[MAX_LINE_LENGTH];
	while(fgets(line, sizeof(line), infile) != NULL)
	{
		//if queue is full, wait
		while(count == max_queue_size);

		//enqueue
		omp_set_lock(&lock);
		enq(line);
		omp_unset_lock(&lock);

		//hit end of file
		if(feof(infile))
		{
			break;
		}
	}
	fclose(infile);

	#pragma omp critical
	prod_count++;
}

void consume()
{
	do
	{
		char line[MAX_LINE_LENGTH];
		while(count == 0 && (prod_count != num_producers));	
		omp_set_lock(&lock);
		deq(line);
		omp_unset_lock(&lock);

		//tokenize
		char* save_ptr;
		char* temp = strtok_r(line, " ", &save_ptr);
		while(temp)
		{		
			#pragma omp critical
			fprintf(output, "%s\n", temp);

			temp = strtok_r(NULL, " ", &save_ptr);
		}
	}
	while(!empty() && prod_count != num_producers);
}

/*
*	QUEUE METHODS
*/
/* Create an empty queue */
void create()
{
    front = rear = NULL;
    count = 0;
}

/* Enqueing the queue */
void enq(char* data)
{
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = malloc(MAX_LINE_LENGTH * sizeof(char));
        strcpy(rear->info, data);
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->info = malloc(MAX_LINE_LENGTH * sizeof(char));
        strcpy(temp->info, data);
        temp->ptr = NULL;
 
        rear = temp;
    }
    count++;
}

/* Dequeing the queue */
void deq(char* dest)
{
    front1 = front;
 
    if (front1 == NULL)
    {
        return;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
            strcpy(dest, front->info);
            free(front);
            front = front1;
        }
        else
        {
            strcpy(dest, front->info);
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
}

/* Returns the front element of queue */
void frontelement(char* dest)
{
    if ((front != NULL) && (rear != NULL))
        strcpy(dest, front->info);
}
 
/* Display if queue is empty or not */
int empty()
{
     if ((front == NULL) && (rear == NULL))
        return 1;
    else
       return 0;
}

