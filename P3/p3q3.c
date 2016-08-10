#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <ctype.h>

#define MAX_LETTERS_PER_WORD 128

void countWordLength();
void printResults();

int thread_count;
int leftover_data;
int data_per_thread;
long long int* countArray;
long char_count;
char* file_name;

int main(int argc, char* argv[])
{
  struct timespec start, stop;

	//usage is num procs, char.ct, infile
	thread_count = strtol(argv[1], NULL, 10);
  char_count = strtol(argv[2], NULL, 10);
  file_name = malloc(128 * sizeof(char));
  strcpy(file_name, argv[3]);

	//init counter array
	countArray = calloc(MAX_LETTERS_PER_WORD, sizeof(long long int));

	data_per_thread = char_count / thread_count;
	leftover_data = char_count % thread_count;

  //begin timing the main focus of the program, counting word length frequency
  clock_gettime(CLOCK_REALTIME, &start);

	//distribute thread work 
	#pragma omp parallel num_threads(thread_count)
	countWordLength();

  //stop time when done
  clock_gettime(CLOCK_REALTIME, &stop);
  printf("Time taken to count words and print results: %ld seconds %ld nanoseconds\n", 
    stop.tv_sec - start.tv_sec, stop.tv_nsec - start.tv_nsec);
}

void countWordLength()
{
	long my_rank = omp_get_thread_num();
	int start;
 	int end;
 	int num_elems_to_use;
 	if(leftover_data > 0)
 	{
  	if(my_rank < leftover_data)
    	{
      	num_elems_to_use = data_per_thread + 1;
       	if(my_rank < leftover_data && my_rank > 0)
       	{
          	start = my_rank * num_elems_to_use;
          	end = (my_rank + 1) * num_elems_to_use;  
       	}
       	else
       	{
          	start = 0;
          	end = num_elems_to_use;  
       	}
    	}
    	else
    	{
      	num_elems_to_use = data_per_thread;
      	start = my_rank * num_elems_to_use + 1;
      	end = start + num_elems_to_use;
    	}
 	}
 	else
 	{
  	start = my_rank * data_per_thread;
  	end = start + data_per_thread;
 	}

  FILE *infile;
  infile = fopen(file_name, "r");
  int c;
  int count = 0;

  //check to make sure at beginning of word
  //if not space, seek back till space, start = this new value
  int check;
  fseek(infile, start, SEEK_SET);
  if(my_rank != 0)
  {
    int f;
    for(f = 0; f <  MAX_LETTERS_PER_WORD; f++)
    {
      if((check = fgetc(infile)) != 32)
      {
        fseek(infile, -2, SEEK_CUR);
      }
      else if(check == 32)
      {
        start = start - f + 1;
        break;
      }
    }
  }
  check = 0;
  //fseek to end ptr, if not space, seek backwards till hit space, set end to that value
  if(my_rank != thread_count - 1)
  {
    fseek(infile, end, SEEK_SET);
    int e;
    for(e = 0; e <  MAX_LETTERS_PER_WORD; e++)
    {
      if((check = fgetc(infile)) != 32)
      {
        fseek(infile, -2, SEEK_CUR);
      }
      else if(check == 32)
      {
        end = end - e + 1;
        break;
      }
    }
  }
  else
    end = char_count;

  //seek to start
  fseek(infile, start, SEEK_SET);
  //iterate and count
  int fgetcCounter = 0;
  while (fgetcCounter < end - start) {
    c = fgetc(infile);
    //while c is not space and within valid char range c++ and counter++
    if(c >= 33 && c < 255)
    {
      count++;
    }
    //when c is space or newline, increment counter value in array and set counter to 0, continue to end
    else if(c == 32 || c == 10 || c == 13 || c == 9)
    {
      #pragma omp critical
      if(count > 0)
      {
        countArray[count]++;
      }

      count = 0;
    }
    fgetcCounter++;
  }
  fclose(infile);

 	#pragma omp barrier

 	if(my_rank == 0)
 	{
 		printResults();
 	}
}

void printResults()
{
  printf("Word Length\tFrequency\n");
  printf("-------------------------\n");
  int x;
  int count = 0;
  for(x = 0; x < MAX_LETTERS_PER_WORD; x++)
  {
    if(countArray[x] > 0)
    {
      count += countArray[x];
      printf("%d\t\t%lld\n", x, countArray[x]);
    }
  }
}