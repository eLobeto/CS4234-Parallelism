/*

 Trivial MPI example.

 Adds up 1000 numbers in an array, where the values are first
 read from a file.

*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1000

int main(int argc, char *argv[])
{
   int myid, numprocs;
   int data[MAXSIZE], i, x, low, high, myresult=0, result=0;
   char fn[255] = "rand_data.txt";
   FILE *fp;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   if (myid == 0)  {      /* Open input file and initialize data */
      if ((fp = fopen(fn,"r")) == NULL) {
         printf("Can't open the input file: %s\n\n", fn);
         exit(1);
      }
      for(i=0; i<MAXSIZE; i++) fscanf(fp,"%d", &data[i]);
   }

   //divide elements
   int elemsPerProc = MAXSIZE / numprocs;
   int extraElems = MAXSIZE % numprocs;

   int* displs = (int *) malloc(sizeof(int) * numprocs);
   int* sendcounts = (int *) malloc(sizeof(int) * numprocs);
   int ctr = 0;
   for(ctr; ctr < numprocs; ctr++)
   {
      //populate sendcounts
      if(myid < extraElems)
      {
         sendcounts[ctr] = elemsPerProc + 1;
         displs[ctr] = elemsPerProc + 1;
      }
      else
      {
         sendcounts[ctr] = elemsPerProc;
         displs[ctr] = elemsPerProc; 
      }
   }

   //create recv buffers
   int* recvbuff = (int *) calloc(elemsPerProc + 1, sizeof(int));
   
   /* broadcast data */
   MPI_Scatterv(data, sendcounts, displs, MPI_INT, recvbuff,
       elemsPerProc + 1, MPI_INT, 0, MPI_COMM_WORLD);

   /* Add my portion of data */
   //sum with extra elems
   if(myid < extraElems)
   {
      int sumCtrM = 0;
      for(sumCtrM; sumCtrM < elemsPerProc + 1; sumCtrM++)
      {
         myresult += recvbuff[sumCtrM];
      }
   }
   //sum with normal amount of elements
   else
   {
      int sumCtr = 0;
      for(sumCtr; sumCtr < elemsPerProc; sumCtr++)
      {
         myresult += recvbuff[sumCtr];
      }
   }
   printf("I got %d from %d\n", myresult, myid);

   /* Compute global sum */
   MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   if (myid == 0) printf("The sum is %d.\n", result);

   free(displs);
   free(sendcounts);
   free(recvbuff);

   MPI_Finalize();
}