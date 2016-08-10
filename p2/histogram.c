/* File:      histogram.c
 * Purpose:   Build a histogram from some random data
 * 
 * Compile:   gcc -g -Wall -o histogram histogram.c
 * Run:       ./histogram <bin_count> <min_meas> <max_meas> <data_count>
 *
 * Input:     None
 * Output:    A histogram with X's showing the number of measurements
 *            in each bin
 *
 * Notes:
 * 1.  Actual measurements y are in the range min_meas <= y < max_meas
 * 2.  bin_counts[i] stores the number of measurements x in the range
 * 3.  bin_maxes[i-1] <= x < bin_maxes[i] (bin_maxes[-1] = min_meas)
 * 4.  DEBUG compile flag gives verbose output
 * 5.  The program will terminate if either the number of command line
 *     arguments is incorrect or if the search for a bin for a 
 *     measurement fails.
 *
 * IPP:  Section 2.7.1 (pp. 66 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num_threads, data_per_thread, leftover_data, thread_finished_ctr;
float* data;
int* bin_counts;
int bin_count, bin, data_count;
float min_meas, max_meas;
float* bin_maxes;
pthread_mutex_t* bin_locks;
pthread_mutex_t barrier_lock;
pthread_cond_t completed;

void* handle_bins(void* rank);

void Usage(char prog_name[]);

void Get_args(
      char*    argv[]        /* in  */,
      int*     num_threads_p   /* in  */,
      int*     bin_count_p   /* out */,
      float*   min_meas_p    /* out */,
      float*   max_meas_p    /* out */,
      int*     data_count_p  /* out */);

void Gen_data(
      float   min_meas    /* in  */, 
      float   max_meas    /* in  */, 
      float   data[]      /* out */,
      int     data_count  /* in  */);

void Gen_bins(
      float min_meas      /* in  */, 
      float max_meas      /* in  */, 
      float bin_maxes[]   /* out */, 
      int   bin_counts[]  /* out */, 
      int   bin_count     /* in  */);

int Which_bin(
      float    data         /* in */, 
      float    bin_maxes[]  /* in */, 
      int      bin_count    /* in */, 
      float    min_meas     /* in */);

void Print_histo(
      float    bin_maxes[]   /* in */, 
      int      bin_counts[]  /* in */, 
      int      bin_count     /* in */, 
      float    min_meas      /* in */);

int main(int argc, char* argv[]) {

   /* Check and get command line args */
   if (argc != 6) Usage(argv[0]); 
   Get_args(argv, &num_threads, &bin_count, &min_meas, &max_meas, &data_count);

   /* Allocate arrays needed */
   bin_maxes = malloc(bin_count*sizeof(float));
   bin_counts = malloc(bin_count*sizeof(int));
   data = malloc(data_count*sizeof(float));

   /* Generate the data */
   Gen_data(min_meas, max_meas, data, data_count);

   /* Create bins for storing counts */
   Gen_bins(min_meas, max_meas, bin_maxes, bin_counts, bin_count);

   data_per_thread = data_count / num_threads;
   leftover_data = data_count % num_threads;
   thread_finished_ctr = 0;
   bin_locks = malloc(bin_count * sizeof(pthread_mutex_t));
   int q;
   for(q = 0; q < bin_count; q++)
   {
      pthread_mutex_init(&bin_locks[q], NULL);
   }
   pthread_mutex_init(&barrier_lock, NULL);
   /* Count number of values in each bin in parallel*/
   //init threads
   pthread_t* thread_handles = malloc(num_threads * sizeof(pthread_t));
   long i;
   for(i = 0; i < num_threads; i++)
   {
      pthread_create(&thread_handles[i], NULL, handle_bins, (void *) i);
   }

   //join threads
   for(i = 0; i < num_threads; i++)
   {
      pthread_join(thread_handles[i], NULL);
   }

#  ifdef DEBUG
   printf("bin_counts = ");
   for (i = 0; i < bin_count; i++)
      printf("%d ", bin_counts[i]);
   printf("\n");
#  endif

   //cleanup
   int z;
   for(z = 0; z < bin_count; z++)
   {
      pthread_mutex_destroy(&bin_locks[z]);
   }
   pthread_mutex_destroy(&barrier_lock);
   free(bin_locks);
   free(data);
   free(bin_maxes);
   free(bin_counts);
   return 0;

}  /* main */

void* handle_bins(void* rank)
{
   long my_rank = (long) rank;
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

   //create local bins
   int local_bin;
   int* local_bin_cts;
   float* local_bin_maxes;
   local_bin_maxes = malloc(bin_count*sizeof(float));
   local_bin_cts = malloc(bin_count*sizeof(int));
   Gen_bins(min_meas, max_meas, local_bin_maxes, local_bin_cts, bin_count);

   //sort data
   int i;
   for(i = start; i < end; i++)
   {
      local_bin = Which_bin(data[i], local_bin_maxes, bin_count, min_meas);
      local_bin_cts[local_bin]++;
   }

   //combine data into main bins
   int j, k;
   for(j = 0; j < bin_count; j++)
   {
      pthread_mutex_lock(&bin_locks[j]);
      for (k = 0; k < local_bin_cts[j]; k++)
      {
         bin_counts[j]++;
      }
      pthread_mutex_unlock(&bin_locks[j]);
   }

   //barrier and wait for all threads to complete
   pthread_mutex_lock(&barrier_lock);
   thread_finished_ctr++;
   if(thread_finished_ctr == num_threads)
   {
      thread_finished_ctr = 0;
      pthread_cond_broadcast(&completed);
   }
   else
   {
      while(pthread_cond_wait(&completed, &barrier_lock) != 0);
   }
   pthread_mutex_unlock(&barrier_lock);

   //print histogram if thread is rank 0
   if(my_rank == 0)
   {
      Print_histo(bin_maxes, bin_counts, bin_count, min_meas);
   }

   //free arrays
   free(local_bin_cts);
   free(local_bin_maxes);
}


/*---------------------------------------------------------------------
 * Function:  Usage 
 * Purpose:   Print a message showing how to run program and quit
 * In arg:    prog_name:  the name of the program from the command line
 */
void Usage(char prog_name[] /* in */) {
   fprintf(stderr, "usage: %s ", prog_name); 
   fprintf(stderr, "<thread_count> <bin_count> <min_meas> <max_meas> <data_count>\n");
   exit(0);
}  /* Usage */


/*---------------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get the command line arguments
 * In arg:    argv:  strings from command line
 * Out args:  bin_count_p:   number of bins
 *            min_meas_p:    minimum measurement
 *            max_meas_p:    maximum measurement
 *            data_count_p:  number of measurements
 */
void Get_args(
      char*    argv[]        /* in  */,
      int*     num_threads_p   /* out  */,
      int*     bin_count_p   /* out */,
      float*   min_meas_p    /* out */,
      float*   max_meas_p    /* out */,
      int*     data_count_p  /* out */) {

   *num_threads_p = strtol(argv[1], NULL, 10);
   *bin_count_p = strtol(argv[2], NULL, 10);
   *min_meas_p = strtof(argv[3], NULL);
   *max_meas_p = strtof(argv[4], NULL);
   *data_count_p = strtol(argv[5], NULL, 10);

#  ifdef DEBUG
   printf("bin_count = %d\n", *bin_count_p);
   printf("min_meas = %f, max_meas = %f\n", *min_meas_p, *max_meas_p);
   printf("data_count = %d\n", *data_count_p);
#  endif
}  /* Get_args */


/*---------------------------------------------------------------------
 * Function:  Gen_data
 * Purpose:   Generate random floats in the range min_meas <= x < max_meas
 * In args:   min_meas:    the minimum possible value for the data
 *            max_meas:    the maximum possible value for the data
 *            data_count:  the number of measurements
 * Out arg:   data:        the actual measurements
 */
void Gen_data(
        float   min_meas    /* in  */, 
        float   max_meas    /* in  */, 
        float   data[]      /* out */,
        int     data_count  /* in  */) {
   int i;

   srandom(0);
   for (i = 0; i < data_count; i++)
      data[i] = min_meas + (max_meas - min_meas)*random()/((double) RAND_MAX);

#  ifdef DEBUG
   printf("data = ");
   for (i = 0; i < data_count; i++)
      printf("%4.3f ", data[i]);
   printf("\n");
#  endif
}  /* Gen_data */


/*---------------------------------------------------------------------
 * Function:  Gen_bins
 * Purpose:   Compute max value for each bin, and store 0 as the
 *            number of values in each bin
 * In args:   min_meas:   the minimum possible measurement
 *            max_meas:   the maximum possible measurement
 *            bin_count:  the number of bins
 * Out args:  bin_maxes:  the maximum possible value for each bin
 *            bin_counts: the number of data values in each bin
 */
void Gen_bins(
      float min_meas      /* in  */, 
      float max_meas      /* in  */, 
      float bin_maxes[]   /* out */, 
      int   bin_counts[]  /* out */, 
      int   bin_count     /* in  */) {
   float bin_width;
   int   i;

   bin_width = (max_meas - min_meas)/bin_count;

   for (i = 0; i < bin_count; i++) {
      bin_maxes[i] = min_meas + (i+1)*bin_width;
      bin_counts[i] = 0;
   }

#  ifdef DEBUG
   printf("bin_maxes = ");
   for (i = 0; i < bin_count; i++)
      printf("%4.3f ", bin_maxes[i]);
   printf("\n");
#  endif
}  /* Gen_bins */


/*---------------------------------------------------------------------
 * Function:  Which_bin
 * Purpose:   Use binary search to determine which bin a measurement 
 *            belongs to
 * In args:   data:       the current measurement
 *            bin_maxes:  list of max bin values
 *            bin_count:  number of bins
 *            min_meas:   the minimum possible measurement
 * Return:    the number of the bin to which data belongs
 * Notes:      
 * 1.  The bin to which data belongs satisfies
 *
 *            bin_maxes[i-1] <= data < bin_maxes[i] 
 *
 *     where, bin_maxes[-1] = min_meas
 * 2.  If the search fails, the function prints a message and exits
 */
int Which_bin(
      float   data          /* in */, 
      float   bin_maxes[]   /* in */, 
      int     bin_count     /* in */, 
      float   min_meas      /* in */) {
   int bottom = 0, top =  bin_count-1;
   int mid;
   float bin_max, bin_min;

   while (bottom <= top) {
      mid = (bottom + top)/2;
      bin_max = bin_maxes[mid];
      bin_min = (mid == 0) ? min_meas: bin_maxes[mid-1];
      if (data >= bin_max) 
         bottom = mid+1;
      else if (data < bin_min)
         top = mid-1;
      else
         return mid;
   }

   /* Whoops! */
   fprintf(stderr, "Data = %f doesn't belong to a bin!\n", data);
   fprintf(stderr, "Quitting\n");
   exit(-1);
}  /* Which_bin */

/*---------------------------------------------------------------------
 * Function:  Print_histo
 * Purpose:   Print a histogram.  The number of elements in each
 *            bin is shown by an array of X's.
 * In args:   bin_maxes:   the max value for each bin
 *            bin_counts:  the number of elements in each bin
 *            bin_count:   the number of bins
 *            min_meas:    the minimum possible measurment
 */
void Print_histo(
        float  bin_maxes[]   /* in */, 
        int    bin_counts[]  /* in */, 
        int    bin_count     /* in */, 
        float  min_meas      /* in */) {
   int i, j, ctr;
   float bin_max, bin_min;
   ctr = 0;
   for (i = 0; i < bin_count; i++) {
      bin_max = bin_maxes[i];
      bin_min = (i == 0) ? min_meas: bin_maxes[i-1];
      printf("%.3f-%.3f:\t", bin_min, bin_max);
      for (j = 0; j < bin_counts[i]; j++)
      {
         printf("X");
         ctr++;
      }
      printf("\n");
   }
   printf("%d\n", ctr);
}  /* Print_histo */