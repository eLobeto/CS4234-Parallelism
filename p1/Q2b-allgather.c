
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define NREPS 10
#define NMAX  1048576
#define Min(a, b) (a > b ? b : a)

int main(int argc, char *argv[])
{
   int myid, numprocs;
   int i, k, seed, count;
   double *data, *data_local;
   struct drand48_data drand_buf;
   double starttime, endtime, mintime;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   data       = (double *) malloc (NMAX * numprocs * sizeof (double));
   data_local = (double *) malloc (NMAX * sizeof (double));
   seed = 1202107158 + MPI_Wtime() * 1999;
   srand48_r (seed, &drand_buf);

   //create random vectors on all processes
   for(i = 0; i < NMAX / numprocs; i++)
   {
    drand48_r(&drand_buf, &data_local[i]);
   }

   count = 1;
   for (k = 0; k<21; k++) {
     mintime = 1000.;
     for (i=0; i<NREPS; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
        starttime = MPI_Wtime();
        MPI_Allgather(data_local, count, MPI_DOUBLE, data, count, MPI_DOUBLE, MPI_COMM_WORLD);
        //Gather all the random data and broadcast it out
        // MPI_Gather(data_local, count, MPI_DOUBLE, data, count, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // MPI_Bcast(data, count*numprocs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        endtime = MPI_Wtime();
        mintime = Min(mintime,endtime-starttime);
     }
     if (myid==0) printf("%8d  %7.3e\n", count, mintime);
     count = count*2;
   }

   MPI_Finalize();
}