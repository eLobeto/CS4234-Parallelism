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
   MPI_Status status;
   int i, x, low, high, myresult=0, result=0;
   char fn[255] = "rand_data.txt";
   FILE *fp;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   int elemsPerProc = MAXSIZE / numprocs;
   int extraElems = MAXSIZE % numprocs;


   int* data = (int *) malloc((elemsPerProc + 1) * sizeof(int));
   int* rootData = (int *) malloc((elemsPerProc + 1) * sizeof(int));
   int* recvbuff = (int *) malloc((elemsPerProc + 1) * sizeof(int));
   if (myid == 0)
   {      
   /* Open input file and initialize data */
      if ((fp = fopen(fn,"r")) == NULL) {
         printf("Can't open the input file: %s\n\n", fn);
         exit(1);
      }
      int ctr = 0;
      int processCtr = 0;
      for(i=0; i<MAXSIZE; i++)
      {
         if(processCtr < extraElems)
         {
            if(processCtr == 0)
            {
               fscanf(fp, "%d", &rootData[ctr]);
               ctr++;
               if(ctr == elemsPerProc + 1)
               {
                  ctr = 0;
                  processCtr++;
                  continue;
               }  
            }
            else
            {
               fscanf(fp,"%d", &data[ctr]);
               ctr++;
               if(ctr == elemsPerProc + 1)
               {
                  MPI_Send(data, elemsPerProc + 1, MPI_INT, processCtr, 0, MPI_COMM_WORLD);
                  ctr = 0;
                  processCtr++;
               }
            }   
         }
         else
         {
            if(processCtr == 0)
            {
               fscanf(fp, "%d", &rootData[ctr]);
               ctr++;
               if(ctr == elemsPerProc)
               {
                  ctr = 0;
                  processCtr++;
                  continue;
               }  
            }
            else
            {
               fscanf(fp,"%d", &data[ctr]);
               ctr++;
               if(ctr == elemsPerProc)
               {
                  MPI_Send(data, elemsPerProc + 1, MPI_INT, processCtr, 0, MPI_COMM_WORLD);
                  ctr = 0;
                  processCtr++;
               }
            }  
         }
      }
   }
   else
   {
      MPI_Recv(recvbuff, elemsPerProc + 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
   }

   /* Add my portion of data */
   if(myid == 0)
   {
      int sumCtrR = 0;
      for(sumCtrR; sumCtrR < elemsPerProc + 1; sumCtrR++)
      {
         myresult += rootData[sumCtrR];
      }  
   }
   else
   {
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
   }

   printf("I got %d from %d\n", myresult, myid);

   /* Compute global sum */
   MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   if (myid == 0) printf("The sum is %d.\n", result);

   MPI_Finalize();
}