#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define NREPS 10
#define NMAX  524288
#define Min(a, b) (a > b ? b : a)

int main(int argc, char *argv[])
{
   int myid, numprocs;
   int  i, k, count;
   int *buf;
   double global_min;
   double starttime, endtime, delta, mintime;
   MPI_Status status;

   buf = (int *) malloc (NMAX * sizeof (int));
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   count = 1;
   for (k = 0; k<20; k++) {
     mintime = 1000.;
     for (i=0; i<NREPS; i++) 
     {
       MPI_Barrier(MPI_COMM_WORLD);
       starttime = MPI_Wtime();
       if (myid == 0 || myid == 1) {
         MPI_Send (buf, count, MPI_INT, 2, 0, MPI_COMM_WORLD);
         MPI_Send (buf, count, MPI_INT, 3, 0, MPI_COMM_WORLD);
       } 
       else {
         MPI_Recv (buf, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
         MPI_Recv (buf, count, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
       }
       endtime   = MPI_Wtime();
       delta = 0.5*(endtime - starttime);
       mintime = Min(mintime,delta);
       MPI_Reduce(&mintime, &global_min, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
     } 
     if (myid==0) printf("%8d  %7.3e  %7.3e\n", count, global_min, (4.0*count)/(global_min*1024.*1024.));
     count = count*2;
   }

   MPI_Finalize();
}